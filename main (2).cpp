#include<iostream>
#include<map>
#include<vector>
#include<queue>
using namespace std;





//definindo uma aresta com elementos: custo, vértice de partida, e vértice de destino
struct Aresta {
	int custo;
	string vPartida;
	string vDestino;
};

vector<Aresta> listaDeArestas; //declarando vetor  para conter itens da lista de 
                              //arestas e nomeando como listaDeArestas. E.g.: (2,A,B), (1,B,C)...
 

//overloading para comparar arestas por custo
struct CompareAresta {
	bool operator()(const Aresta &a, const Aresta &b) {
		return a.custo > b.custo; //checa se determinada aresta tem maior ou menor
		                         //custo em relação a outra, e retorna verdadeiro ou falso
	}
};  


int main()
{  
	priority_queue<Aresta, vector<Aresta>, CompareAresta> pq;   //declarando fila de prioridades
	                                                           //<tipoDeElemento, container, regraDeComparação >

//tipo de elemento--> Aresta
//container -->vector<Aresta> (onde as arestas são depositadas)
//regraDeComparação --> overload de bool operator() que retorna a aresta menos custosa
//pq --> codinome para priority_queue


	//declarando vértices e inicializando como não visitados
	//utilizando estrutura map<chave, valor>, onde cada chave única tem valor verdadeiro ou falso (visitado ou não visitado)
	map<string, bool>visitados; 
	visitados["Areias"] = false; //"inicializando vértice A como não visitado"...
	visitados["Boa Viagem"] = false;
	visitados["Ibura"] = false;
	visitados["Imbiribeira"] = false;
	visitados["Ipsep"] = false;
	visitados["Pina"] = false;    



//declarando lista de adjacência (representação do grafo)
    map<string, vector<Aresta>> adj;

    //criando grafo
    adj["Areias"].push_back({2,"Areias","Ipsep"});  //"vértice A tem aresta adjacente de custo 2 ligando a B"...
    adj["Areias"].push_back({3,"Areias","Ibura"});
    
    
    adj["Boa Viagem"].push_back({4,"Boa Viagem","Pina"});           
    adj["Boa Viagem"].push_back({4,"Boa Viagem","Imbiribeira"});
    
    adj["Ibura"].push_back({3,"Ibura","Areias"});
    adj["Ibura"].push_back({1,"Ibura","Ipsep"});
    
    adj["Imbiribeira"].push_back({4,"Imbiribeira","Boa Viagem"});
    adj["Imbiribeira"].push_back({4,"Imbiribeira","Ipsep"});
    adj["Imbiribeira"].push_back({6,"Imbiribeira","Pina"});
    
    adj["Ipsep"].push_back({1,"Ipsep","Ibura"});
    adj["Ipsep"].push_back({4,"Ipsep","Imbiribeira"});
    adj["Ipsep"].push_back({2,"Ipsep","Areias"});
    
    adj["Pina"].push_back({6,"Pina","Imbiribeira"});
    adj["Pina"].push_back({4,"Pina","Boa Viagem"}); 
    
    //pedindo o vértice inicial para o usuário
    string inicio;
    cout<<"Escolha o bairro inicial (Areias, Boa Viagem, Ibura, Imbiribeira, Ipsep): "<<endl;
    getline(cin, inicio);    
    cout<<endl;
    

visitados[inicio] = true; //adicionando vértice inserido pelo usuário aos visitados
cout<<"Bairros visitados: "<<"["<<inicio<<"]"<<endl; 
cout<<endl;



for (auto &aresta : adj[inicio]) //para cada aresta contida em adj[inicio] (arestas adjacentes ao vertice inicial): 
{                   
    pq.push(aresta); //enviar aresta para pq (fila de prioridades)
}


//-------------------------------Lógica do Algoritmo de Prim--------------------------------------------------------------------------------
while (!pq.empty()) { //enquanto pq (fila de prioridades) não estiver vazia:
    Aresta a = pq.top(); // declara uma variável a do tipo Aresta e à ela envia a aresta do topo de pq (fila de prioridades)
    pq.pop(); // remove a aresta do topo de pq (aresta que foi adicionada à "Aresta a")

    if (visitados[a.vDestino] == true ) //checa se o vértice já foi visitado
         continue; //se o vértice já tiver sido visitado, o algoritmo retorna para a próxima iteração

    listaDeArestas.push_back(a);      // adicionar aresta do topo da fila de prioridades à lista de arestas
    visitados[a.vDestino] = true;     // marcar novo vértice descoberto como visitado

    
    for (auto &aresta : adj[a.vDestino]) { // para cada aresta adjacente ao vértice de destino:
        if (!visitados[aresta.vDestino]) // se o vértice não tiver sido visitado:
        pq.push(aresta); // adicionar aresta à fila
    }
// a partir daqui, a lista de arestas está completa. A lógica a seguir é referente ao custo total e visualização
    
     int custoTotal=0;   
     cout<<endl;
     cout<<"-----------------------------------------"<<endl;
     
     
    cout<<"Bairros conectados: "<<endl;
    for (auto &a : listaDeArestas) { //para cada aresta na lista de arestas:
    cout << a.vPartida << " - " << a.vDestino << " (custo: R$" << a.custo*5<<".000" << ")\n"; // exibir aresta e custo no seguinte formato:
                                                                                 // A - B (custo: 2)
    custoTotal += a.custo;  //adicionar custo da aresta analisada ao custo total
    cout<<endl;
} 

////////////////////Aqui é a lógica para exibir os vértices visitados//////////////////////////////////////////////
   cout << "Bairros visitados: [";
for (auto &v : visitados) {    
    if (v.second==true) { // só imprime se já foi visitado
        cout << v.first <<" "; 
        
        //v.first é relacionada à chave do map e v.second é relacionado ao valor booleano
        //então v.first retorna um vértice, e v.second retorna se ele foi visitado ou não
        //visitados["Areias"] = false;   "Areias" é v.first, false é v.second
    }
    
}
cout<<"]";

cout << endl;
////////////////////////////////////////////////////////////////////
cout << "Custo total: R$" << custoTotal*5<<".000" << endl; //exibir custo total


}


 

//---------------------------------------------------------------------------------------------------------------




	return 0;
}


//-----------------------------------------------------------------------------------------------------------------

//pseudocódigo (alto nível de abstração):
//1.selecionar vértice inicial e marcá-lo como visitado      
//2.listar todas as arestas desse vértice com vértices não visitados
//3.adicionar arestas listadas à fila de prioridade
//4.A ordenação por custo é feita dentro da lógica de priority_queue
//5.adicionar primeira aresta com vertice não visitado da fila de prioridades à lista de arestas
//6.adicionar o novo vértice vistado à lista de visitados
//7.Repetir passos 2 a 7 até que todos os vértices sejam visitados

//-----------------------------------------------------------------------------------------------------------------

//pseudocódigo (baixo nível de abstração):
//1.Selecionar vértice inicial e marcá-lo como visitado
//2.Mandar todas as suas arestas para pq (fila de prioridades)
//3.Enquanto a fila de prioridades não estiver vazia:
//  .pop() aresta mais barata
//  .se o destino dessa aresta não estiver visitado:
//     .push_back() aresta à lista de arestas
//     .marcar vDestino como visitado
//     .mandar arestas com vizinhos não visitados para fila de prioridades
//4.parar quando todos os vértices forem visitados

//-----------------------------------------------------------------------------------------------------------------

