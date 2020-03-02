#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

int N;

class offer {
public:
	int number;
	int cost;
	int player;
	offer(int player = 0, int number = 0, int cost = 0) {
		this->number = number;
		this->cost = cost;
		this->player = player;
	}
};

class player {
public:
	const bool RANK = false;//RANK == true <=> player is a bank
	player() {
		this->money = 10'000;
		this->q_ESM = 4;
		this->q_EGP = 2;
		this->q_factories = 2;
		this->q_mech_factories = 0;
	}
	void give_money(int sum) {
		this->money -= sum;
	}

	void change_ESM(bool rank, int d_q) {
		if (rank) {
			this->q_ESM += d_q;
		}
	}

	void change_EGP(bool rank, int d_q) {
		if (rank) {
			this->q_EGP += d_q;
		}
	}
	int get_money() const {
		return this->money;
	}
	int get_EGP()const {
		return this->q_EGP;
	}
	int get_ESM() const {
		return this->q_ESM;
	}
	int get_factories() const {
		return this->q_factories;
	}
	int get_mech_factories() const {
		return this->q_mech_factories;
	}

	void build_factory(int building_type) {// building_type: 0 - обычная, 1 - автоматизированная, 2 - перестройка обычной
		if (this->new_factories.size() + this->q_factories + this->q_mech_factories == 6) {
			return;
		}
		this->new_factories.push_back((building_type << 12 | 0));//первое число - тип строимой фабрики, 2 - кол-во месяцев
		if (building_type == 0) {
			this->money -= 2500;
		}
		else if (building_type == 1) {
			this->money -= 5000;
		}
		else {
			this->money -= 3500;
		}
	}

	void make_EGP(int count, bool factory_type) {// int factory_type: 0 - common, 1 - mechanical
		if (factory_type) {
			if (this->q_mech_factories * 2 < count || this->money < (count >> 1) * 3000 + (count & 1) * 2000 || count > this->q_ESM) {
				return;
			}
			q_ESM -= count;
			q_EGP += count;
			this->money -= (count >> 1) * 3000 + (count & 1) * 2000;
		}
		else {
			if (this->q_factories < count || this->money < count * 2000 || count > this->q_ESM) {
				return;
			}
			q_ESM -= 1;
			q_EGP += 1;
			this->money -= 2000 * count;
		}
	}

	/*void get_loan(int sum) {

	}*/

	void step_update() {
		this->money -= this->q_ESM * 300 + this->q_EGP * 500 + q_factories * 1000 + q_mech_factories * 1500;
		for (auto it = this->new_factories.begin(); it < this->new_factories.end(); ++it) {
			int& f = *it;
			int month = (f & 1111), type = (f >> 12);
			if (type == 0) {
				if (month == 4) {
					this->money -= 2500;
				}
				else if (month == 5) {
					this->new_factories.erase(it);
					this->q_factories += 1;
				}
				else {
					f = ((type << 12) | (month + 1));
				}
			}
			else if (type == 1) {
				if (month == 6) {
					this->money -= 5000;
				}
				else if (month == 7) {
					this->new_factories.erase(it);
					this->q_mech_factories += 1;
				}
				else {
					f = ((type << 12) | (month + 1));
				}
			}
			else if (type == 3) {
				if (month == 8) {
					this->money -= 3500;
				}
				else if (month == 9) {
					this->new_factories.erase(it);
					this->q_factories -= 1;
					this->q_mech_factories -= 1;
				}
				else {
					f = ((type << 12) | (month + 1));
				}
			}
		}
	}

private:
	int money, q_ESM, q_EGP, q_factories, q_mech_factories;
	vector<int> new_factories;
};

ostream& operator<<(ostream& out, player const& pl) {
	out << "--- player info ---";
	out << "Money: " << pl.get_money() << endl;
	out << "Q_ESM: " << pl.get_ESM() << endl;
	out << "Q_EGP: " << pl.get_EGP() << endl;
	out << "Q_FACTORIES: " << pl.get_factories() << endl;
	out << "Q_MECH_FACTORIES: " << pl.get_mech_factories() << endl;
	out << "-----------------------------------------------------------------\n";
	return out;
}

class Bank {
public:
	const bool RANK = true;//RANK == true <=> player is a bank
	Bank() {
		this->offer_level = 3;
		this->step = 0;
	}

	void clear_offers() {
		this->offers.clear();
	}

	void bank_update() {
		this->offers.clear();
		++this->step;
		int p = rand() % 12;
		if (this->offer_level == 1) {
			switch (p) {
			case 0: { p = 1; break; }
			case 1: {p = 1; break; }
			case 2: {p = 1; break; }
			case 3: {p = 1; break; }
			case 4: {p = 2; break; }
			case 5: {p = 2; break; }
			case 6: {p = 2; break; }
			case 7: {p = 2; break; }
			case 8: {p = 3; break; }
			case 9: {p = 3; break; }
			case 10: {p = 4; break; }
			case 11: {p = 5; break; }
			}
		}
		else if (this->offer_level == 2) {
			switch (p) {
			case 0: { p = 1; break; }
			case 1: {p = 1; break; }
			case 2: {p = 1; break; }
			case 3: {p = 2; break; }
			case 4: {p = 2; break; }
			case 5: {p = 2; break; }
			case 6: {p = 2; break; }
			case 7: {p = 3; break; }
			case 8: {p = 3; break; }
			case 9: {p = 3; break; }
			case 10: {p = 4; break; }
			case 11: {p = 5; break; }
			}
		}
		else if (this->offer_level == 3) {
			switch (p) {
			case 0: { p = 1; break; }
			case 1: {p = 2; break; }
			case 2: {p = 2; break; }
			case 3: {p = 2; break; }
			case 4: {p = 3; break; }
			case 5: {p = 3; break; }
			case 6: {p = 3; break; }
			case 7: {p = 3; break; }
			case 8: {p = 4; break; }
			case 9: {p = 4; break; }
			case 10: {p = 4; break; }
			case 11: {p = 5; break; }
			}
		}
		else if (this->offer_level == 4) {
			switch (p) {
			case 0: { p = 1; break; }
			case 1: {p = 1; break; }
			case 2: {p = 1; break; }
			case 3: {p = 1; break; }
			case 4: {p = 2; break; }
			case 5: {p = 2; break; }
			case 6: {p = 2; break; }
			case 7: {p = 2; break; }
			case 8: {p = 3; break; }
			case 9: {p = 3; break; }
			case 10: {p = 4; break; }
			case 11: {p = 5; break; }
			}
		}
		else if (this->offer_level == 5) {
			switch (p) {
			case 0: { p = 1; break; }
			case 1: {p = 1; break; }
			case 2: {p = 1; break; }
			case 3: {p = 1; break; }
			case 4: {p = 2; break; }
			case 5: {p = 2; break; }
			case 6: {p = 2; break; }
			case 7: {p = 2; break; }
			case 8: {p = 3; break; }
			case 9: {p = 3; break; }
			case 10: {p = 4; break; }
			case 11: {p = 5; break; }
			}
		}
		this->offer_level = p;
	}

	void make_new_offer(offer& of) {
		this->offers.push_back(of);
	}

	int get_elder() const {
		return this->step % N;
	}

	vector<offer> get_offers(bool rank)const {
		if (rank) {
			return offers;
		}
	}

	vector<int> get_bank_offers() const {
		return this->offer_level_table[this->offer_level];
	}
private:
	//const int TABLE[5][4] = { {2, 800, 6, 6500}, {3, 650, 5, 6000}, {4, 500, 4, 5500}, {5, 400, 3, 5000}, {6, 300, 2, 4500} };
	const vector<vector<int>> offer_level_table = { {2, 800, 6, 6500}, {3, 650, 5, 6000}, {4, 500, 4, 5500}, {5, 400, 3, 5000}, {6, 300, 2, 4500} };
	vector<offer> offers;
	char offer_level;
	int step;
};


void torgi(vector<player>& pl, Bank& bank) {
	auto bank_ofs = bank.get_bank_offers();
	cout << "Q_ESM: " << bank_ofs[0] << "/2 ||| min cost:" << bank_ofs[1] << endl;
	for (int i = 0; i < pl.size(); ++i) {
		cout << "Player #" << i + 1 << ", please, enter your offers of ESM\n";
		cout << "Enter number of offers: "; int q; cin >> q;
		for (int c = 0; c < q; ++c) {
			cout << "Enter number of ESM: "; int n;	cin >> n;
			cout << "Enter cost of ESM: "; int cost; cin >> cost;
			if (cost > bank_ofs[0]) {
				offer o(i, n, cost);
				bank.make_new_offer(o);
			}
		}
	}
	auto of = bank.get_offers(bank.RANK);
	sort(of.begin(), of.end(), [&](offer& left, offer& right)
		{
			if (left.cost == right.cost) {
				int elder = bank.get_elder();
				return (right.player == elder);
			}
			else {
				return left.cost > right.cost;
			}
		});
	int ESM = N * bank_ofs[0] / 2;
	for (int i = 0; i < of.size() && ESM > 0; ++i) {
		auto t = of[i];
		pl[t.player].give_money(t.cost * min(t.number, ESM));
		pl[t.player].change_ESM(bank.RANK, min(t.number, ESM));
		cout << "Player #" << t.player + 1 << " got " << min(t.number, ESM) << " ESMs for " << t.cost << "$\n";
	}
	bank.clear_offers();
}


void sell(vector<player>& pl, Bank& bank) {
	auto bank_ofs = bank.get_bank_offers();
	cout << "Q_EGP: " << bank_ofs[2] << "/2 ||| max cost:" << bank_ofs[3] << endl;
	for (int i = 0; i < pl.size(); ++i) {
		cout << "Player #" << i + 1 << ", please, enter your offers of ESM\n";
		cout << "Enter number of offers: "; int q; cin >> q;
		for (int c = 0; c < q; ++c) {
			cout << "Enter number of ESM: "; int n;	cin >> n;
			cout << "Enter cost of ESM: "; int cost; cin >> cost;
			if (cost <= bank_ofs[3]) {
				offer o(i, n, cost);
				bank.make_new_offer(o);
			}
		}
	}
	auto of = bank.get_offers(bank.RANK);
	sort(of.begin(), of.end(), [&](offer& left, offer& right)
		{
			if (left.cost == right.cost) {
				int elder = bank.get_elder();
				return (right.player == elder);
			}
			else {
				return left.cost < right.cost;
			}
		});
	int EGP = N * bank_ofs[2] / 2;
	for (int i = 0; i < of.size() && EGP > 0; ++i) {
		auto t = of[i];
		pl[t.player].give_money(t.cost * min(t.number, EGP));
		pl[t.player].change_EGP(bank.RANK, min(t.number, EGP));
		cout << "Player #" << t.player + 1 << " got " << min(t.number, EGP) << " ESMs for " << t.cost << "$\n";
	}
	bank.clear_offers();
}

int main() {
	srand(time(0));
	Bank bank;
	cout << "Enter N: "; cin >> N;
	vector<player> pl(N);
	for (int i = 0; i < 20; ++i) {
		torgi(pl, bank);
		sell(pl, bank);
		for (int j = 0; j < N; ++j) {
			cout << "Player #" << j + 1 << "what player do ypu want to get info? (0 - nobody, 1 - " << N << ")\n";
			int q;
			cin >> q;
			if (q > 0) {
				cout << pl[q - 1] << endl;
			}
		}
		bank.bank_update();
	}
	return 0;
}