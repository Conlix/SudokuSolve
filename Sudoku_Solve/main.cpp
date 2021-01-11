#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <fstream>

std::vector<std::vector<int>> pspalt;
std::vector<int> pspalt_k;

std::vector<std::vector<int>> pline;
std::vector<int> pline_k;

std::vector<std::vector<int>> fealds;
std::vector<int> fziff;
int nfeald;
int zfeald;

std::vector<std::vector<std::vector<int>>> fild;
std::vector<std::vector<int>> zeile;
std::vector<int> ziff;

std::vector<std::vector<int>> display;
std::vector<int> diszeil;

int changepos(int x, int y, int z);
int create();
int print();
int get_input();
int checkfeald();
int checkline();
int checkspalt();
int checkpos();
int inputfile();

int main() {
	time_t t;
	srand((unsigned)time(&t));
	create();
	inputfile();
	int f = 1;
	while (f == 1) {
		f = 0;
		if (f == 0) {
			f = checkfeald();
		}
		if (f == 0) {
			f = checkline();
		}
		if (f == 0) {
			f = checkspalt();
		}
		if (f == 0) {
			f = checkpos();
		}
	}
	print();
	int end;
	std::cin.clear();
	std::cin >> end;
}

int inputfile() {
	std::ifstream reader("input.txt");
	if (reader.is_open()) {
		int ix, iy, iz;
		while (reader >> ix >> iy >> iz) {
			changepos(ix, iy, iz);
		}
	}
	print();
	std::cout << '\n';
	std::cout << "Sudoku in Progress" << std::endl;
	std::cout << '\n';
	return(0);
}

int checkpos() {
	int found = 0;
	for (int y = 0; y < 9; y++) {
		zeile = fild[y];
		for (int x = 0; x < 9; x++) {
			if (zeile[x].size() == 1) {
				found = 1;
				ziff = zeile[x];
				changepos(x, y, ziff[0]);
				break;
			}
		}
		if (found == 1) {
			break;
		}
	}
	return(found);
}
int checkspalt() {
	int found = 0;
	for (int cs = 0; cs < 9; cs++) {
		pspalt_k = pspalt[cs];
		for (int cn = 0; cn < 9; cn++) {
			if (pspalt_k[cn] == 1) {
				for (int cy = 0; cy < 9; cy++) {
					zeile = fild[cy];
					ziff = zeile[cs];
					for (int zn = 0; zn < zeile[cs].size(); zn++) {
						if (ziff[zn] == cn + 1) {
							found = 1;
							changepos(cs, cy, cn + 1);
							break;
						}
					}
					if (found == 1) {
						break;
					}
				}
				break;
			}
		}
		if (found == 1) {
			break;
		}
	}
	return(found);
}
int checkline() {
	int found = 0;
	for (int cl = 0; cl < 9; cl++) {
		pline_k = pline[cl];
		for (int cn = 0; cn < 9; cn++) {
			if (pline_k[cn] == 1) {
				//Find Koodinates
				zeile = fild[cl];
				for (int kn = 0; kn < 9; kn++) {
					ziff = zeile[kn];
					for (int zn = 0; zn < ziff.size(); zn++) {
						if (ziff[zn] == cn + 1) {
							changepos(kn, cl, cn + 1);
							found = 1;
							break;
						}
					}
					if (found == 1) {
						break;
					}
				}
				break;
			}
		}
		if (found == 1) {
			break;
		}
	}
	return(found);
}
int checkfeald() {
	int found = 0;
	for (int cf = 0; cf < 9; cf++) {
		fziff = fealds[cf];
		for (int cn = 0; cn < 9; cn++) {
			if (fziff[cn] == 1) {
				int xko = (cf % 3) * 3;
				int yko = (cf / 3) * 3;
				for (int y = yko; y < yko + 3; y++) {
					zeile = fild[y];
					for (int x = xko; x < xko + 3; x++) {
						ziff = zeile[x];
						for (int zn = 0; zn < ziff.size(); zn++) {
							if (ziff[zn] == cn + 1) {
								changepos(x, y, cn + 1);
								found = 1;
								break;
							}
						}
						if (found == 1) {
							break;
						}
					}
					if (found == 1) {
						break;
					}
				}
				break;
			}
			if (found == 1) {
				break;
			}
		}
	}
	return(found);
}
int get_input() {
	int ix = -1;
	int iy = -1;
	int iz = -1;
	std::string end;
	while (end != "end") {
		ix = -1;
		iy = -1;
		iz = -1;
		while (ix <= -1 || ix >= 9) {
			std::cout << "X: ";
			std::cin >> ix;
		}
		while (iy <= -1 || iy >= 9) {
			std::cout << "Y: ";
			std::cin >> iy;
		}
		while (iz <= -1 || iz >= 10) {
			std::cout << "Z: ";
			std::cin >> iz;
		}
		std::cin.clear();
		std::cout << "end for end input and w for next input: ";
		std::cin >> end;

		changepos(ix, iy, iz);
		system("CLS");
		print();
	}
	return(0);
}
int changepos(int x, int y, int z) {
	diszeil = display[y];
	diszeil[x] = z;
	display[y] = diszeil;
	//emty feald
	for (int zei = 0; zei < 9; zei++) {
		zeile = fild[zei];
		if (zei == y) {
			for (int k = 0; k < 9; k++) {
				ziff = zeile[k];
				if (k == x) {
					//Update Spalt
					pspalt_k = pspalt[x];
					for (int cs = 0; cs < ziff.size(); cs++) {
						pspalt_k[ziff[cs] - 1]--;
					}
					pspalt[x] = pspalt_k;
					//Update line
					pline_k = pline[y];
					for (int cl = 0; cl < ziff.size(); cl++) {
						pline_k[ziff[cl] - 1]--;
					}
					pline[y] = pline_k;
					//emty feald
					int nk = (y / 3) * 3 + k / 3;
					fziff = fealds[nk];
					for (int c = 0; c < ziff.size(); c++) {
						fziff[ziff[c] - 1]--;
					}
					fealds[nk] = fziff;

					ziff.clear();
					zeile[k] = ziff;
				}
				for (int n = 0; n < ziff.size(); n++) {
					if (z == ziff[n]) {
						ziff.erase(ziff.begin() + n);
						zeile[k] = ziff;
						//Update Spalt
						pspalt_k = pspalt[k];
						pspalt_k[z - 1]--;
						pspalt[k] = pspalt_k;

						//Update line

						pline_k = pline[y];
						pline_k[z - 1]--;
						pline[y] = pline_k;
						//Unpdate fealds

						int nk = (zei / 3) * 3 + k / 3;
						fziff = fealds[nk];
						fziff[z - 1]--;
						fealds[nk] = fziff;
					}
				}
			}
			fild[zei] = zeile;
		}
		else {
			ziff = zeile[x];
			for (int n = 0; n < ziff.size(); n++) {
				if (ziff[n] == z) {
					ziff.erase(ziff.begin() + n);
					zeile[x] = ziff;
					fild[zei] = zeile;
					//Update Spalt
					pspalt_k = pspalt[x];
					pspalt_k[z - 1]--;
					pspalt[x] = pspalt_k;
					//Update line
					pline_k = pline[zei];
					pline_k[z - 1]--;
					pline[zei] = pline_k;
					//Unpdate fealds
					int nk = (zei / 3) * 3 + x / 3;
					fziff = fealds[nk];
					fziff[z - 1]--;
					fealds[nk] = fziff;
				}
			}
		}
	}
	int kx = round((x) / 3);
	int ky = round((y) / 3);
	int xsrt = 0;
	int ysrt = 0;
	int xend = 0;
	int yend = 0;
	xsrt = kx * 3;
	ysrt = ky * 3;
	xend = xsrt + 3;
	yend = ysrt + 3;
	for (int zei = ysrt; zei < yend; zei++) {
		zeile = fild[zei];
		for (int k = xsrt; k < xend; k++) {
			ziff = zeile[k];
			for (int n = 0; n < ziff.size(); n++) {
				if (ziff[n] == z) {
					ziff.erase(ziff.begin() + n);
					//Update Spalt
					pspalt_k = pspalt[k];
					pspalt_k[z - 1]--;
					pspalt[k] = pspalt_k;

					//Update line
					pline_k = pline[zei];
					pline_k[z - 1]--;
					pline[zei] = pline_k;

					//Unpdate fealds
					int nk = (zei / 3) * 3 + x / 3;
					fziff = fealds[nk];
					fziff[z - 1]--;
					fealds[nk] = fziff;
				}
			}
			zeile[k] = ziff;
		}
		fild[zei] = zeile;
	}
	return(0);
}
int print() {
	for (int z = 0; z < 9; z++) {
		diszeil = display[z];
		for (int k = 0; k < 9; k++) {
			std::cout << diszeil[k] << " ";
			if (k == 2 || k == 5) {
				std::cout << " ";
			}
		}
		std::cout << '\n';
		if (z == 2 || z == 5) {
			std::cout << '\n';
		}
	}
	return(0);
}
int create() {
	pspalt.clear();
	for (int ps = 0; ps < 9; ps++) {
		pspalt_k.clear();
		for (int psk = 0; psk < 9; psk++) {
			pspalt_k.push_back(9);
		}
		pspalt.push_back(pspalt_k);
	}
	pline.clear();
	for (int pl = 0; pl < 9; pl++) {
		pline_k.clear();
		for (int plk = 0; plk < 9; plk++) {
			pline_k.push_back(9);
		}
		pline.push_back(pline_k);
	}
	fealds.clear();
	for (int f = 0; f < 9; f++) {
		fziff.clear();
		for (int fz = 0; fz < 9; fz++) {
			fziff.push_back(9);
		}
		fealds.push_back(fziff);
	}
	display.clear();
	for (int z = 0; z < 9; z++) {
		diszeil.clear();
		for (int k = 0; k < 9; k++) {
			diszeil.push_back(0);
		}
		display.push_back(diszeil);
	}
	fild.clear();
	for (int l = 0; l < 9; l++) {
		zeile.clear();
		for (int z = 0; z < 9; z++) {
			ziff.clear();
			for (int i = 0; i < 9; i++) {
				ziff.push_back(i + 1);
			}
			zeile.push_back(ziff);
		}
		fild.push_back(zeile);
	}
	std::vector<std::vector<int>> zout = fild[8];
	std::vector<int> iout = zout[8];
	int out = iout[8];
	return(out);
}