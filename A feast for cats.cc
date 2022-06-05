#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define fastio() cin.tie(nullptr); cout.tie(nullptr); ios_base::sync_with_stdio(false);
#define lli long long int
//https://open.kattis.com/problems/cats
struct UnionFind{
	vector<lli> father;
	vector<lli> size;
	lli numConj;
	UnionFind(lli n): father(n),size(n,1),numConj(n){
		for(lli i=0;i<n;i++) father[i] = i;
	}
	lli find(lli u){
	return father[u] = (u == father[u]? u: find(father[u]));
	}
	void union_set(lli u, lli v){
		auto u_father = find(u);
		auto v_father = find(v);
		if(u_father != v_father){
			numConj--;
			if(size[u_father] < size[v_father]) swap(u_father, v_father);
			father[v_father] = u_father;
		}
	}
	bool same_set(lli u, lli v){
	return find(u) == find(v);
		}
};
struct Arista{
	lli origen,destino,peso;
	Arista(lli origen,lli destino, lli peso):origen(origen), destino(destino),peso(peso){};
	bool operator <(const Arista& e){
	return peso < e.peso;
	}
};
bool operator<(const Arista& a,const Arista& b){
		return a.peso > b.peso;
	}
struct Grafo{
	vector<vector<Arista>> lista_ad;
	vector<Arista> aristas;
	lli V;
	Grafo(lli n): lista_ad(n), V(n){}
	void agregar_arista(lli u, lli v, lli peso){
		lista_ad[u].push_back(Arista(u,v,peso));
		lista_ad[v].push_back(Arista(v,u,peso));
		aristas.push_back({u,v,peso});
	}
	vector<Arista> kruskal(){
		vector<Arista> minimum_spanning_tree_kruskal;
		UnionFind uf(V);
		sort(aristas.begin(),aristas.end());
		for(Arista& e: aristas){
			if(!uf.same_set(e.origen,e.destino)){
				uf.union_set(e.origen,e.destino);
				minimum_spanning_tree_kruskal.push_back(e);
			}
		if(minimum_spanning_tree_kruskal.size() == V-1) break;
		}
	return minimum_spanning_tree_kruskal;
	}
	void procesa(lli u, priority_queue<Arista>& pq, vector<bool>& usada){
		usada[u] = true;
		for(Arista& e: lista_ad[u]){
			if(!usada[e.destino]){
				pq.push(e);
			}
		}
	}
	vector<Arista> prim(){
		priority_queue<Arista> pq;
		vector<bool> visitado(V);
		vector<Arista> minimum_spanning_tree_prim;
		procesa(0,pq,visitado);
		while(!pq.empty()){
			Arista e = pq.top(); pq.pop();
			if(visitado[e.destino]) continue;
			minimum_spanning_tree_prim.push_back(e);
			procesa(e.destino,pq,visitado);
			if(minimum_spanning_tree_prim.size() == V-1) break;
		}
		return minimum_spanning_tree_prim;
	}
};
void solve(){
	auto n=0,m=0; cin >> n >> m;
	lli x = (m*(m-1)/2);
	Grafo g(n); lli total1=0,total2=0;
	for(auto i=0;i<x;i++){
		lli u,v,w;
		cin >> u >> v >> w;
		g.agregar_arista(u,v,w);
	}
	auto mst1 = g.prim();
	lli total=0;
	for(Arista& e: mst1){
		total+= e.peso;
		}
	if((total+m) > n){
		cout << "no" << endl;
		return;
	}
	cout << "yes" << endl;
return;
}
int main(){
	fastio();
	auto t=0; cin >> t;
	while(t--) solve();
	return 0;
	}
