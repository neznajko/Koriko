#include <iostream>
#include <sstream>
#include <vector> 
#include <algorithm>
using namespace std;
/*                                             macros */
#define NL   '\n' 
#define M    4 // West-East (>)
#define N    3 // North-South streets (v)
////////////////////////////////////////////////////////
struct Point {
	int coor[2]; // SeaLevl
	friend
	bool operator==(const Point &lft, const Point &ryt)
	{
		return (lft.coor[0] == ryt.coor[0] and
				lft.coor[1] == ryt.coor[1]);
	}
	friend
	ostream &operator<<(ostream &out, const Point &p)
	{
		out << "(" << p.coor[0] 
			<< "," << p.coor[1] << ")";

		return out;
	}
};
typedef vector<Point> line_t;
/*                                        global data */
double SeaLevl[M][N] = {{ +3.5, +1.3, +0.0 },
						{ +8.7, +5.2, -4.5 },
						{ -3.1, -2.0, -1.5 },
						{ +0.1, +3.5, +2.3 }};
line_t *gates[M][N];
vector<line_t *> stk;  /*   shtack  */
Point A{1, 0};
Point B{0, 1};
/*	,	>	:	!	-	*	'	=	+	@	.	h	- */
line_t *variants(int hrz, int vrt)
// get all possible variants from that point
{
    int fset = 1; // wtf? (offset)
    int i, j;
	const double levl = SeaLevl[hrz][vrt];
	line_t *var = new line_t;

    // loof around (hrz, vrt) point N, (W, E), S
    for (i = hrz - 1; i < hrz + 2; i += 1) {
        fset = !fset;
        if (i < 0 or i >= M) continue;
        for (j = vrt - fset; j < vrt + 2; j += 2) {
            if (j < 0 or j >= N) continue;
			if (SeaLevl[i][j] > levl) continue;
			var->push_back({i, j});
        }
	}
	return var;
}
/*	-	1	>	,	>	<	0	\\	.	/	o	,	. */
void set_gates(void)
{
	for (int m=0; m<M; m++) {
		for (int n=0; n<N; n++) {
			gates[m][n] = variants(m, n);
		}
	}
}
/*	.	8	g	-	8	.	e	8	l	-	g	-	z */
void walk(const Point &src, line_t *aux) /* tree walk */
// tree walk
{
	static Point const &dst = B;
	
	aux->push_back(src);

	if (src == dst) {
		
		stk.push_back(aux);
		
		return;
	}
	auto [hrz, vrt] = src.coor; // unpack
	
	for (const auto &p: *gates[hrz][vrt]) {
		if (find(aux->begin(), aux->end(), p) != aux->end())
		 	continue; // have found
		line_t *copy = new line_t(*aux); // copy Ninja Kakashi
		walk(p, copy);
	}
	// clear
	aux->clear();
	delete aux;
}
void dunf(line_t vec) // yeeh!
{
	stringstream ss;

	for (auto &p: vec) ss << p << ' ';

	cout << ss.str();
}
int main(void)
{
	set_gates();

	walk(A, new line_t);

	cout << stk.size() << NL;

	dunf(*stk[0]);

	return 0;
}
/////////////////////////////////////////////////// log:
// - S, He Mu ce KapaG! (4yBaE 7u?)
