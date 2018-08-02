#include "Maillage.hpp"


using namespace std;




int main(int argc, const char ** argv)
{
	Maillage Th(argv[1]);
    //Maillage Th2(argv[2]);
	Th.gnuplot("Th.gp");
	//Th2.gnuplot("th2.gp");
    
    int t;
    
    // On le met dans le main ou la class Maillage ?
    int (*arete)[2]= new int[3* Th.nt][2];
    multimap <pair<int,int>,int> M;
    multimap<int, int> M_som_trian;
    int nombre_e= ConstructionArete(Th,arete,M);
    cout<< "  Nombre aretes  "<<nombre_e<<endl<<endl;
    
    
    // Point
    R2 P(0.5,1.2);
    //R2 P(-0.7,0.5);
    //R2 P(10,0);
    bool trouve=false;
    std::cout<<" point:    "<<P<<std::endl<<std::endl;
    int numtrianginit=4; //n° du triangle de depart
    //cout <<"coordonnees des 3 sommets du triangle 4 :"<< Th.t[4](0) << endl <<Th.t[4](1)<<endl <<Th.t[4](2)<<endl;
    //cout <<"coordonnees des 3 sommets du triangle 0 :"<< Th.t[0](0) << endl <<Th.t[0](1)<<endl <<Th.t[0](2)<<endl;
    //cout <<"coordonnees du point du triangle 22 :"<< Th.t[22](0) << endl <<Th.t[22](1)<<endl <<Th.t[22](2)<<endl;

    
     	//cout<<"le triangle trouve est : "<<Th.MiseAJour(P,4,M)<<endl;
    
       t=Th.MiseAJour(P, 4, M);
       cout << "le numero du triangle trouve est :"<< t << endl;
    if(t!=-1){
       cout <<"coordonnees des 3 sommets du triangle :"<<endl << Th.t[t](0) << endl <<Th.t[t](1)<<endl <<Th.t[t](2)<<endl;
    }
    
    //lancement pour plusieurs points




	cout<<endl<<endl<<endl<<endl<<endl;
  // question4(Th,Th2,M,M_som_trian);


    cout<<endl<<endl<<endl<<endl<<endl;
    multimap<int,int>::iterator it;
    int count =0;
    for(it=M_som_trian.begin(); it!=M_som_trian.end();it++){
        cout<< "sommet : "<< it->first  << " dans le triangle : " <<it->second<<endl;
        count +=1;
        cout<< " compteur de triangle" <<count<<endl;

    }
 
    
    
   
   
    
	return 0;
}



//      Question peux ton faire variable globale pour donner un x_min x_max y_min y_max


// Test si (i,j ) dans la map
// 1) oui => arete exisste
//    k'=edj(i,j)

//2) non => on rajoute edj(i,j)=3*h+e
//                     adj(3*h+e)=-1
 
 
 
 
 
 
 
 
 
 /*
 int S_local_0=  (i+1)%3;
 int S_local_1= (i+2)%3;
 if(S_local_1<S_local_0){
     echange(sommet_0,S_local_1);
 }
 int S_global_0
 bool Trouve_adj = false;
 if(Trouve_adj  == false){
      //Triangle k n'a pas d'adjacent à son arete arete_i
      //Le point est en dehors du maillage
 }
 }
 
 */








