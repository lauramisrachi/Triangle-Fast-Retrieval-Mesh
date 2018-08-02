#include "Maillage.hpp"
#include <fstream>
#include <iostream>
#include <cassert>
#include <map>
#include <utility>


using namespace std;

Maillage::Maillage(const char *filename)
{
	std::ifstream f(filename);
    
    if(f.is_open())
    {
        cout << "Le fichier est bien ouvert " << endl;
    }
    else
    {
        cout << " Le fichier n'est pas ouvert correctement" <<  endl;
        
        return;
    }
    
	assert(f);
	int notused,l,i1,i2,i3;
	R2 P; 
	f >> ns >> nt >> notused;
	s.resize(ns);
	t.resize(nt);
	for(int i=0; i< ns; ++i)
	{
		f >> P >> l;
		s[i].R2::operator=(P);
		s[i].lab=l;
		s[i].nu = i;
        s[i].point = P; 

	}
	for(int i=0; i< nt; ++i)
	{
		f >> i1>> i2>> i3 >> l; 
		t[i].s[0]= &s[i1-1];
		t[i].s[1]= &s[i2-1];
		t[i].s[2]= &s[i3-1];
	}
	//MiseAJour();
    std::cout << " on a fini la lecture de " << filename
		 << " ns "<< ns << " nt " << nt <<" min  "<< std::endl;
}



void Maillage::gnuplot(const char *filename)
{
	std::ofstream f(filename);
	assert(f);
	for( int k=0; k<nt; ++k)
	{
		
		f 	<< (R2) *t[k].s[0] << "\n"
			<< (R2) *t[k].s[1] << "\n"
			<< (R2) *t[k].s[2] << "\n"		
			<< (R2) *t[k].s[0] << "\n\n";		
				
			
	}
	
}
int Maillage::MiseAJour(R2 P, int point_depart, multimap<pair<int, int>,int>& M)
{
    bool trouve=false;
    int numtrianginit=point_depart;
    while(trouve == false){
        Triangle Q =t[numtrianginit];
        
        cout<<"num triangle init : "<<numtrianginit<<endl;
        int i = 0; // retour triangle adjacent
        int (*sauv)[2]= new int[2][2];
        sauv[0][0]=-1;
        sauv[0][1]=-1;
        sauv[1][0]=-1;
        sauv[1][1]=-1;
    
        double a1=calcul_aire(Q(0),Q(1),P);
        double a2=calcul_aire(Q(0),P,Q(2));
        double a3=calcul_aire(P,Q(1),Q(2));
        int nbre_neg=0;
    
        /*
         std::cout<<"aire de a1   "<<a1<<"     point 0    "<<Q(0)<<   "    rand   "<<rand()<< std::endl<<std::endl;
        std::cout<<"aire de a2   "<<a2<<"     point 1    "<<Q(1)<< std::endl<<std::endl;
        std::cout<<"aire de a3   "<<a3<<"     point 2    "<<Q(2)<<"  aire negative   " <<nbre_neg <<std::endl<<std::endl;
         */
        
        if (a1>=0 && a2>=0 && a3>=0){
            std::cout<<" On est dans le bon triangle   "<<numtrianginit<< std::endl;
            trouve=true;
            return numtrianginit;
        }
    
        if(a1<0){
            sauv[nbre_neg][0]=0;
            sauv[nbre_neg][1]=1;
            nbre_neg++;
        }
        if(a2<0){
            sauv[nbre_neg][0]=0;
            sauv[nbre_neg][1]=2;
            nbre_neg++;
        }
        if(a3<0){
            sauv[nbre_neg][0]=1;
            sauv[nbre_neg][1]=2;
            nbre_neg++;
        }
    
        
        if ( nbre_neg==2){
            
            // random
            int j = rand();
            
            //cout<<"choix de l'arete"<<endl;
            //cout<<sauv[j][0]<<endl;
            
            
            // ici on renvoie le numéro global de sommet de l'arrete considérée
            int a = Q[sauv[j][0]];
            int b = Q[sauv[j][1]];
            if( b<a) echange(a,b);
            //cout<<Q.label(sauv[j][0])<<endl;
            //cout<<"dans if en dehors du tableau"<<endl;
            //cout<<"les sommets globaux sont "<<a<<' '<<b<<endl;
            // i=Trouver triangle adj
            //Q=Th.t[i];
            i = Adjacent(numtrianginit, make_pair(a,b), M);
            if(i==-1){
                j=1-j;
                int a = Q[sauv[j][0]];
                int b = Q[sauv[j][1]];
                
                // i=Trouver triangle adj
                //Q=Th.t[i];
                
                i = Adjacent(numtrianginit, make_pair(a,b), M);
                if(i==-1){
                    cout<<"le point est en dehors du maillage"<<endl;
                    return -1;
                
                }

            }
            
            numtrianginit = i ;
        }
        else{
            
            // i=Trouver triangle adj
            //Q=Th.t[i];
            int a = Q[sauv[0][0]];
            int b = Q[sauv[0][1]];
            if(b<a) echange(a,b);
            //cout<<"label "<<Q.label(sauv[0][0])<<endl;
            //cout<<"les sommets globaux sont "<<a<<' '<<b<<endl;
            cout<<"adj: "<<a<<' '<<b<<endl;
            i=Adjacent(numtrianginit, make_pair(a,b), M);
            
            if(i==-1){
                cout<<"Le point est en dehors du maillage"<<endl;
                return -1;
            }
            numtrianginit = i ;
            cout<<"triangle i "<<i<<endl;
            
        }
    }
return 0;
}


int Maillage::Adjacent(int triangle,pair<int,int> arete, multimap<pair<int, int>,int> &M){
    if(M.count(arete)<2){
        return -1;
    }else{
        std::pair <multimap<pair<int,int>,int>::iterator, multimap<pair<int,int>,int>::iterator> ret;
        ret = M.equal_range(arete);
        for (multimap<pair<int,int>,int>::iterator it=ret.first; it!=ret.second; ++it){
            if(it->second!=triangle)
                return it->second;
        }
        cout<<"la fonction adjacent ne marche pas : pb!!!!!"<<endl;
        return -1;
    }
    
}


int ConstructionArete(const Maillage & Th,int (* arete)[2], multimap<pair<int, int>, int> & arete_tab) {  //int (* arete)[2] pointeur sur tableau de 2
    int nbex = 3*Th.nt; // Nombre maximal arrete
    int SommetDesAretes[3][2] = { {1,2},{2,0},{0,1}}; // combinaisons possibles d'arrete locales
    int end_list=-1; // pour effectuer un test
    int * head_minv = new int [Th.ns]; // tête de liste:  but; remplir cette liste pour dire combien il y a d'arrete associée à ce sommet
    int * next_edge = new int [nbex]; //nombre maximal d'arrete : next_edge liste pour
    for ( int i =0;i<Th.ns;i++)
    {
        head_minv[i]=end_list; // on met à -1 partout head_minv :  il n'y a pas encore d'arretes
    }
    
    int nbe = 0; // nombre réel d'arrete dans le maillage
    
     for(int t=0;t<Th.nt;t++){  // boucle sur le tableau de triangles (tableau global)
        for(int et=0;et<3;et++) { // boucle sur les arretes sur un seul tableau
            int i= Th(t,SommetDesAretes[et][0]); //
            int j= Th(t,SommetDesAretes[et][1]); //
            if (j < i) echange(i,j) ;// définir le plus petit en i et le plus grand en j
                bool existe =false; // l’areˆte n’existe pas a priori
            for (int e=head_minv[i];e!=end_list;e = next_edge[e] )
            {
                // On rentre dedans si il y a déjà une arrete de faite
                // on parcourt les areˆtes de ́ja` construites
                if ( arete[e][1] == j) //
                {existe=true;break;
                } // fin de la boucle for ici
            }
            
            //ajout dans la multi_map
            
            arete_tab.insert(make_pair(make_pair(i,j), t));
            
            if (!existe) { // on rentre si arrete n'existe pas
                assert(nbe < nbex);
                arete[nbe][0]=i, arete[nbe][1]=j; // on remplit le tableau d'arrete
                next_edge[nbe]=head_minv[i],head_minv[i]=nbe++;} // but de head_minv donner le nombre
            
            //nbe est l'indice du tableau arete qui fait référence à l'indice
            // l'indice dans le tableaud d'arete (2ème étage) qui donne l'indice ddans tableau arete de la dernierèe arrete construite depuis ce sommet (la valeur est un numéro de sommet).
            
            
            // head :  donne l'indice dans le tableau arrete à regarder pour obtenir la dernière arrete crée pour le sommet en question. Pour traiter du sommet 3, on va a l'indice 3 du tableau head.
            
            // next : pour connaitre les autres arretes créees pour ce meme sommet, on regarde dans le tableau next à l'indice donné par head.
            
            // Dans next, quand il y a un nombre différent de -1, cela signifie que dans le tableau arrete général, à cet indice là, on a les autres arretes crées pour ce sommet. Il n'y en a plus d'autres lorsqu'on tombe sur un -1.
            
            
            // Maintenant, on a besoin de créer une fonction pour déterminer, pour une arrete donnée, à quels triangles elle appartient. ==> puis on effectue le calcul d'aire et on se déplace dans les bonnes directions.
            
            // Pour déterminer le triangle adjacent à une arrete, on regarde dans notre tableau arrete les sommets partagés par les deux sommets de notre arrete et on à notre triangle adjacent lorsqu'on trouve un même sommet partagé par les deux sommets considérés.
        }
        
        
    }
    delete [] head_minv;
    delete [] next_edge;
    return nbe;
    
    //creer une fonction pour une arrete les tableaux soit avec map soit avec multimap
}
 
 





 


double calcul_aire(R2& A,R2& B, R2& C){
    double area=0;
    R2 AB(A,B);
    R2 AC(A,C);
    area=(AB^AC)*0.5;
    return area;
}


int rand(){
    static std::mt19937 generateur(666);
    if((double)generateur()/generateur.max()<0.5)
        return 0;
    else
        return 1;
}


void question4 (Maillage & Th1, Maillage & Th2,multimap<pair<int, int>,int> &M1,multimap<int, int> &M2 ){
   //Cette fonction range dans la multimap M2 chaque sommet du maillage Th2 avec le triangle du maillage Th1 qui le contient.
    
    int T_init =4;
        
    int tri_dep=0;
    //int tri_fin=0;
        
    //creation_map
    int T_final, cpttrian, nsommet,i,sommetglob, T_temp;
        
    //cout<<"avant 1er for maillage"<<endl;
        
    for(int t=0;t<Th2.nt;t++){  // boucle sur le tableau de sommet (tableau global)
        //for(int t=0;t<2;t++){
        cpttrian=0;
        nsommet=0;
        cout<<"avant while maillage"<<endl<<endl<<endl<<endl<<endl<<endl;
        while(cpttrian<1 && nsommet<3){ //permet de tester si un des sommet du triangle trouve et donc avoir un bon triangle de depart
            i=Th2(t,nsommet);
            cout<<"apres instruction i     "<<i<<"  "<<nsommet<<endl;
            if(M2.count(i)!=0){
                cpttrian++;
                T_temp=M2.find(i)->second;
                if(T_temp != -1)
                    T_init = T_temp;
                cout<<"dans le 1er if"<<endl;
                }
            nsommet++;
            cout<<"nsommet : "<<nsommet<<endl;
                    
        }
            cout<<"apres while"<<endl;
            for(int st=0;st<3;st++){
                sommetglob=Th2(t,st); //sommet globale pour chaque sommet
                if (M2.count(sommetglob)==0){
                    cout<<"coordonnées du point : "<<Th2.get_point(t,st)<<endl;
                    cout<<" pb mise  jour : "<<Th2.get_point(t,st)<<"  "<<T_init <<endl<<endl;
                    
                    T_final=Th1.MiseAJour(Th2.get_point(t,st), T_init, M1);
                    cout<<endl<<"j'ai trouve le triangle"<<endl<<endl;
                    M2.insert(make_pair(sommetglob, T_final));
		    if(T_final!=-1){
                    	T_init=T_final; //permet de partir d'un "bon" triangle pour le nv point
		    }
                }
                
            }
        }
        
    }


