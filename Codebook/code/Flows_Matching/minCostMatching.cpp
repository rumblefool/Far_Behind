/*O(n^3) solves 1000x1000 problems in around 1s
cost[i][j] = cost for pairing Li with Rj
Lmate[i]=index of R node that L node i pairs with
Rmate[j]=index of L node that R node j pairs with
cost[i][j] may be +ve or -ve.	To perform
maximization,simply negate the cost[][] matrix.*/
typedef ll cost_type;
typedef vector<cost_type> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

cost_type MCM(const VVD &cost, VI &Lmate, VI &Rmate) {
	int n = int(cost.size()); VD u(n),v(n);
	for (int i = 0; i < n; i++) {
		u[i] = cost[i][0];
		for (int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
	}
	for (int j = 0; j < n; j++) {
		v[j] = cost[0][j] - u[0];
		for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
	}
	Lmate = VI(n, -1); Rmate = VI(n, -1);
	int mated = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Rmate[j] != -1) continue;
			if (fabs(cost[i][j]-u[i]-v[j]) < 1e-10){ 
//**** change this comparision if double cost ****
				Lmate[i]=j; Rmate[j]=i; mated++; break;
			}
		}
	}
	VD dist(n); VI dad(n); VI seen(n);
	while (mated < n) {
		int s = 0;
		while (Lmate[s] != -1) s++;
		fill(dad.begin(), dad.end(), -1);
		fill(seen.begin(), seen.end(), 0);
		for (int k = 0; k < n; k++) 
			dist[k] = cost[s][k] - u[s] - v[k];
		int j = 0;
		while (true) {
			j = -1;
			for (int k = 0; k < n; k++) {
				if (seen[k]) continue;
				if (j == -1 || dist[k] < dist[j]) j = k;
			}
			seen[j] = 1;
			if (Rmate[j] == -1) break;
			const int i = Rmate[j];
			for (int k = 0; k < n; k++) {
				if (seen[k]) continue;
				const cost_type new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					dad[k] = j;
				}
			}
		}
		for (int k = 0; k < n; k++) {
			if (k == j || !seen[k]) continue;
			const int i = Rmate[k];
			v[k] += dist[k]-dist[j]; 
			u[i] -= dist[k]-dist[j];}
		u[s] += dist[j];
		while (dad[j] >= 0) {
			const int d = dad[j];
			Rmate[j]=Rmate[d]; Lmate[Rmate[j]]=j; j=d;}
		Rmate[j] = s; Lmate[s] = j; mated++;
	}
	cost_type value = 0;
	for (int i = 0; i < n; i++)
		value += cost[i][Lmate[i]];
	return value;
}