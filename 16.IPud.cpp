#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <stack>
using namespace std;

using name = string;

class Ipud {
public:
	Ipud() {
		time_list = 0;
		tplay = 0;
	}

	void addSong(string n, string a, int d) {
		if (songs.count(n) != 0) throw std::invalid_argument("addSong");
		else {
			songs.insert({ n,{a,d}});
		}
	}

	void addToPlaylist(string n) {
		if (songs.count(n) == 0 || list.count(n) != 0) throw std::invalid_argument("addToPlaylist");
		else {
			list.insert({n});
			time_list = songs[n].time + time_list;
		}

	}

	string current() {
		if (list.empty()) {
			throw std::domain_error("current");
			return "";
		}
		else {
			auto it = list.begin();
			return (*it);
		}
	}

	string play(bool &b) {
		if (!list.empty()) {
			string s = current();
			played.insert({ s });
			list.erase(s);
			tplay++;
			b = true;
			return s;
		}
		else return "";
	}

	int totalTime() {
		return time_list;
	}

	void deleteSong(string s) {
		if (!songs.empty()) {
			if (songs.count(s) != 0) {
				songs.erase(s);
				if (list.count(s) != 0) list.erase(s);
				if (played.count(s) != 0) played.erase(s);
			}
		}	
	}

	void recent(int n) {
		if (played.empty()) cout << "No hay canciones recientes" << endl;
		else {
			cout << "Las " << n << " mas recientes" << endl;
			stack<string> tmp;
			for (auto it = played.begin(); it != played.end(); it++) {
				tmp.push(*(it));
			}
			int i = 0;
			while (!tmp.empty() && i < n) {
				cout << "    " << tmp.top() << endl;
				tmp.pop();
				i++;

			}
		}
	}

private:
	struct info {
		string artist;
		int time;
	};
	std::unordered_map <name, info> songs;
	std::unordered_set <name> list;
	std::unordered_set <name> played;
	int tplay;
	int time_list;

};


bool tratar_caso() {
	string s;
	cin >> s;
	if (cin.eof()) return false;
	Ipud ipud;
	while (s != "FIN") {
		try {

			if (s == "addSong") {
				string n, a; int d;
				cin >> n >> a >> d;
				ipud.addSong(n, a, d);
			}
			else if (s == "addToPlaylist") {
				string n; cin >> n;
				ipud.addToPlaylist(n);
			}
			else if (s == "play") {
				bool b = false;
				string song = ipud.play(b);
				if(!b) cout << "No hay canciones en la lista" << endl;
				else cout << "Sonando "  << song << endl;
			}
			else if (s == "recent") {
				int n; cin >> n;
				ipud.recent(n);
			}
			else if (s == "totalTime"){
				cout << "Tiempo total " << ipud.totalTime() << endl;
			}
			else if (s == "current") {
				ipud.current();
			}
			else if (s == "deleteSong") {
				string song; cin >> song;
				ipud.deleteSong(song);
			}

		}
		catch (std::exception &e) {
			cout << "ERROR " << e.what() << endl;
		}
		cin >> s;

	}
	ipud.totalTime();
	cout << "---" << endl;
	return true;

}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	//system("PAUSE");
#endif
	return 0;
}