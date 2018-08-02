#include "R2.hpp"
#include <vector>
#include <utility>
#include <map>
#include<random>
int rand();

class Sommet : public R2 {
public:
	int lab ; //    
	int nu; // numero du sommet
    R2 point;  //
	Sommet & operator=(R2 &P) {
		 R2::operator=(P); 
		 return *this;}
};




class Triangle   {
public:
	Sommet * s[3];  // tableau de 3 pointeurs
	//Sommet( * s)[3];  // pointeur sur un tableau

    // methode
    int & operator[](int i) const { return s[i]->nu;}
    R2 & operator()(int i) const { return s[i]->point;}
    int label(int i) const {return s[i]->lab;} //label du sommet i local
    
    //R2 & operator()(int i) const {  R2 p(s[i]->x,s[i]->y); return p;}
//int  aretes[3][2];// tableau de 3 pointeurs qui pointe vers tableau de taille 2 (nums arrete)
};



class Maillage {
public:
	int ns, nt; // nombre de sommets , nombre de triangles
	std::vector<Sommet> s; // tableau de sommet
	std::vector<Triangle> t; // tableau de triangle 
	Maillage(const char *filename);
	void gnuplot(const char *filename);
    int operator()(int it,int j) const {return (t[it][j]);};  // it triangle du Maillage de sommet j
    //R2 & operator{}(int it,int j) const {return (t[it](j));};  // it triangle du Maillage de sommet j
    R2 & get_point(int it,int j) const {return (t[it](j));};  // it triangle du Maillage de sommet j

    Triangle operator[](int j) const {return (t[j]);};  // triangle du Maillage de numero j
	void operator=(const Maillage &);
	// A FAIRE 
     int Adjacent(int triangle,std::pair<int,int> arete, std::multimap<std::pair<int, int>, int> & m);// log(n)

	// vous donnees 
    int MiseAJour(R2 P, int point_depart, std::multimap<std::pair<int, int>,int>& M)  ; // pour cree vos donnees  n lon(n)
private:// pas de copie
    Maillage(const Maillage &);
    
};


int ConstructionArete(const Maillage & Th,int (* arete)[2], std::multimap<std::pair<int, int>, int> & arete_tab) ;  //int (* arete)[2] pointeur sur tableau de 2



double calcul_aire(R2& A,R2& B, R2& C);
    

template<class T> inline void echange (T& a,T& b) {T c=a;a=b;b=c;}
void question4 ( Maillage & Th1, Maillage & Th2,std::multimap<std::pair<int, int>,int> &M1, std::multimap<int,int> &M2);

//benjebrianoor@yahoo.fr
