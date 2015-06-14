#include <iostream>
#include <vector>
#include <queue>
#include <climits>


using namespace std;

const int MAXN = 10010;
typedef long long ll;

int convexHull, N, M, start, finish;

struct canal;

//all hail u know who

struct island{
	vector<canal> outgoing;
	int shortestpath, hull;
	island() {
		shortestpath = INT_MAX; //who cares?
		hull = -1;
	}
};

struct canal{
	island* destination;
	ll weight;
	ll hulldamage;
	
	canal(island* dest, ll w, ll dmg){
		destination = dest;
		weight = w;
		hulldamage = dmg;
	}
};

island islands[MAXN]; //safety
int a, b, c, d;

int totalWeight, damage;

void Dijkstra(){
	queue<island*> toCheck;
	queue<int> distance;
	queue<int> maxHull;

	islands[a].shortestpath = 0;
	
	distance.push(0);
	toCheck.push(&islands[start]);
	maxHull.push(convexHull);

	while(!toCheck.empty()){
		
		island* front = toCheck.front(); 
		int dist = distance.front();
		int height = maxHull.front();

		toCheck.pop();
		maxHull.pop();
		distance.pop();
		
		for(canal &c : front->outgoing){
			int str = height - c.hulldamage;
			int time = dist + c.weight;
			island* destination = c.destination;
			if((time < destination->shortestpath || str > destination->hull) && str > 0){
				destination->shortestpath = std::min(time, destination->shortestpath);
				destination->hull = std::max(destination->hull, str);
				toCheck.push(destination);
				maxHull.push(str);
				distance.push(time);
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &convexHull, &N, &M);
	while(M--){
		scanf("%d%d%d%d", &a, &b, &c, &d);
		islands[a].outgoing.emplace_back(canal(&islands[b], c, d));
		islands[b].outgoing.emplace_back(canal(&islands[a], c, d));
	}
	scanf("%d%d", &start, &finish);
	Dijkstra();
	if(islands[finish].shortestpath == INT_MAX){ //broken..
		printf("-1");
	} else {
		printf("%d", islands[finish].shortestpath);
	}
}
