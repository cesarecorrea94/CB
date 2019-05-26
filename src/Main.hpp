/*
 * Main.h
 *
 *  Created on: 5 de ago de 2018
 *      Author: cesar
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <string.h>
#include <stdio.h>

template<typename type>
type max(type a, type b) {
	return a > b ? a : b;
}
template<typename type, typename ...type_>
type max(type a, type b, type_... c) {
	return max(max(a, b), c...);
}

template<typename type>
type** newMatrix(unsigned rows, unsigned cols) {
	type** matrix = new type*[rows];
	for(unsigned i = 0; i < rows; ++i)
		matrix[i] = new type[cols];
	return matrix;
}
template<typename type>
void delMatrix(type** matrix, unsigned rows, unsigned cols) {
	for(unsigned i = 0; i < rows; ++i)
		delete[] matrix[i];
	delete[] matrix;
}


struct alignmentMatrix {
	const char *A, *B;
	int** self = nullptr;
	enum arrow {
		none = 0b00,
		hori = 0b10,
		vert = 0b01,
		diag = 0b11
	};
	arrow** align = nullptr;
	char* string = nullptr;

	alignmentMatrix(const char* A, const char* B) {
		this->A = A;
		this->B = B;
		this->self  = newMatrix <int> (strlen(A)+1, strlen(B)+1);
		this->align = newMatrix<arrow>(strlen(A)+1, strlen(B)+1);
	}
	~alignmentMatrix() {
		delete this->string;
		delMatrix(this->self,  strlen(A)+1, strlen(B)+1);
		delMatrix(this->align, strlen(A)+1, strlen(B)+1);
	}
	void lcss_comparison() {
		this->self[0][0] = 0;
		this->align[0][0] = none;

		for(unsigned i = 1; i <= strlen(A); ++i) {
			this->self[i][0] = i*0;
			this->align[i][0] = vert;
		}
		for(unsigned j = 1; j <= strlen(B); ++j) {
			this->self[0][j] = j*0;
			this->align[0][j] = hori;
		}

		for(unsigned i = 1; i <= strlen(A); ++i)
			for(unsigned j = 1; j <= strlen(B); ++j) {
				int 	iver = this->self[i-1] [j]  -0,
						idia = this->self[i-1][j-1] + ((A[i-1] == B[j-1]) ? 1 : 0),
						ihor = this->self [i] [j-1] -0;
				this->self[i][j] = max(iver, idia, ihor);
				if(false) {}
				else if(this->self[i][j] == idia) this->align[i][j] = diag;
				else if(this->self[i][j] == iver) this->align[i][j] = vert;
				else if(this->self[i][j] == ihor) this->align[i][j] = hori;
			}
	}
	void levenshtein_comparison() {
		this->self[0][0] = 0;
		this->align[0][0] = none;

		for(unsigned i = 1; i <= strlen(A); ++i) {
			this->self[i][0] = i*-1;
			this->align[i][0] = vert;
		}
		for(unsigned j = 1; j <= strlen(B); ++j) {
			this->self[0][j] = j*-1;
			this->align[0][j] = hori;
		}

		for(unsigned i = 1; i <= strlen(A); ++i)
			for(unsigned j = 1; j <= strlen(B); ++j) {
				int 	iver = this->self[i-1] [j]  -1,
						idia = this->self[i-1][j-1] + ((A[i-1] == B[j-1]) ? 0 : -1),
						ihor = this->self [i] [j-1] -1;
				this->self[i][j] = max(iver, idia, ihor);
				if(false) {}
				else if(this->self[i][j] == idia) this->align[i][j] = diag;
				else if(this->self[i][j] == iver) this->align[i][j] = vert;
				else if(this->self[i][j] == ihor) this->align[i][j] = hori;
			}
	}
	void global_comparison() {
		this->self[0][0] = 0;
		this->align[0][0] = none;

		for(unsigned i = 1; i <= strlen(A); ++i) {
			this->self[i][0] = i*-2;
			this->align[i][0] = vert;
		}
		for(unsigned j = 1; j <= strlen(B); ++j) {
			this->self[0][j] = j*-2;
			this->align[0][j] = hori;
		}

		for(unsigned i = 1; i <= strlen(A); ++i)
			for(unsigned j = 1; j <= strlen(B); ++j) {
				int 	iver = this->self[i-1] [j]  -2,
						idia = this->self[i-1][j-1] + ((A[i-1] == B[j-1]) ? 1 : -1),
						ihor = this->self [i] [j-1] -2;
				this->self[i][j] = max(iver, idia, ihor);
				if(false) {}
				else if(this->self[i][j] == iver) this->align[i][j] = vert;
				else if(this->self[i][j] == idia) this->align[i][j] = diag;
				else if(this->self[i][j] == ihor) this->align[i][j] = hori;
			}
	}
	void local_comparison() {
		this->self[0][0] = 0;
		this->align[0][0] = none;

		for(unsigned i = 1; i <= strlen(A); ++i) {
			this->self[i][0] = 0;
			this->align[i][0] = vert;
		}
		for(unsigned j = 1; j <= strlen(B); ++j) {
			this->self[0][j] = 0;
			this->align[0][j] = hori;
		}

		for(unsigned i = 1; i <= strlen(A); ++i)
			for(unsigned j = 1; j <= strlen(B); ++j) {
				int 	iver = this->self[i-1] [j]  -2,
						idia = this->self[i-1][j-1] + ((A[i-1] == B[j-1]) ? 1 : -1),
						ihor = this->self [i] [j-1] -2,
						inon = 0;
				this->self[i][j] = max(iver, idia, ihor, inon);
				if(		this->self[i][j] == iver) this->align[i][j] = vert;
				else if(this->self[i][j] == idia) this->align[i][j] = diag;
				else if(this->self[i][j] == ihor) this->align[i][j] = hori;
				else if(this->self[i][j] == inon) this->align[i][j] = none;
			}
		throw false; // falta tratar os 'none's da matriz 'align' nas funções 'print'
	}

	int similarity() {
		return this->self[strlen(A)][strlen(B)];
	}

	void aux(char* &_to, const char* _from, arrow cond) {
		*(_to++) = '\n';
		for(int i = strlen(A), j = strlen(B); 0 < i && 0 < j; ) {
			arrow _align = this->align[i][j];
			*(_to++) = (_align & cond) ? *(_from--) : '_';
			if(_align & vert) { --i; }
			if(_align & hori) { --j; }
		}
	}

	const char* print(){
		if(this->string != nullptr) {
			return this->string;
		}
		this->string = new char[3*(strlen(A)+3+strlen(B))];
		char* ptr = this->string;
		aux(ptr, &A[strlen(A)-1], vert);
		*(ptr++) = '\n';
		for(int i = strlen(A), j = strlen(B); 0 < i && 0 < j; ) {
			arrow _align = this->align[i][j];
			*(ptr++) = (_align != diag) ? ' ' :
					(A[i-1] == B[j-1]) ? '|' : 'X';
			if(_align & vert) { --i; }
			if(_align & hori) { --j; }
		}
		aux(ptr, &B[strlen(B)-1], hori);
		return this->string;
	}

	void printMatrix() {
		for(unsigned i = 0; i <= strlen(A); ++i) {
			for(unsigned j = 0; j <= strlen(B); ++j) {
				printf("%5i", this->self[i][j]);
			}
			puts("\n");
		}
	}

};

#endif /* MAIN_HPP_ */

