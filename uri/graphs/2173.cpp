#include <bits/stdc++.h>

using namespace std;
using edge = tuple<int, int, int>;

class union_find {
private:
	vector<int> parents, rank;
	int size;

public:
	union_find(int n) : parents(n + 1), rank(n + 1, 0), size(n) {
		for(int u = 1; u <= n; ++u) {
			parents[u] = u;
		}
	}

	int find_set(int u) {
		return u == parents[u] ? u : (parents[u] = find_set(parents[u]));
	}

	bool same_set(int u, int v) {
		return find_set(u) == find_set(v);
	}

	void union_set(int u, int v) {
		if(not same_set(u, v)) {
			int x = find_set(u), y = find_set(v);
			if(rank[x] >= rank[y]) {
				parents[y] = parents[x];
			} else {
				parents[x] = parents[y];
			}

			if(rank[x] == rank[y]) ++rank[x];

			--size;
		}
	}

	int count(void) {
		return size;
	}
};


int main(void) {
	int n, m;
	while(scanf("%d %d", &n, &m), n | m) {
		vector<edge> edges;
		for(int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			edges.push_back(edge(w, u, v));
		}

		sort(edges.begin(), edges.end());

		union_find ufds = union_find(n);
		set<edge> min_spanning_tree, max_spanning_tree;
		for(int i = 0; i < edges.size() && ufds.count() > 1; ++i) {
			int w, u, v;
			tie(w, u, v) = edges[i];
			if(not ufds.same_set(u, v)) {
				min_spanning_tree.insert(edges[i]);
				ufds.union_set(u, v);
			}
		}

		ufds = union_find(n);
		for(int i = edges.size() - 1; i >= 0 && ufds.count() > 1; --i) {
			int w, u, v;
			tie(w, u, v) = edges[i];
			if(not ufds.same_set(u, v)) {
				max_spanning_tree.insert(edges[i]);
				ufds.union_set(u, v);
			}
		}

		set<edge> max_st, min_st;
		set_difference(max_spanning_tree.begin(), max_spanning_tree.end(), min_spanning_tree.begin(), min_spanning_tree.end(), inserter(max_st, max_st.end()));
		set_difference(min_spanning_tree.begin(), min_spanning_tree.end(), max_spanning_tree.begin(), max_spanning_tree.end(), inserter(min_st, min_st.end()));

		int max_st_cost = 0, min_st_cost = 0;
		for(auto& current_edge : max_st) {
			int w, u, v;
			tie(w, u, v) = current_edge;
			max_st_cost += w;
		}

		for(auto& current_edge : min_st) {
			int w, u, v;
			tie(w, u, v) = current_edge;
			min_st_cost += w;
		}

		printf("%d\n", max_st_cost - min_st_cost);
	}
	return 0;
}
