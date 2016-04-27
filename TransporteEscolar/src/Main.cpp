#include "Graph.h"
#include "Empresa.h"
#include "Recursos.h"
#include "Excecoes.h"
#include "Mapa.h"
#include "graphviewer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
/*
 * VERIFICAR se quando se remove um cliente, se existe mais algum cliente que marca
 * a escola ou a aquela casa , caso contrario deixam de ser pontos de interesse no mapa
 */
//CLIENTE
//==============================================================================================================

void addCliente(Empresa *e){
	string nome;
	Morada *casa = new Morada();
	Morada *escola = new Morada();
	int id;

	clrscr();
	displayTitulo("ADICIONAR CLIENTE");

	cout << "Nome: ";
	cin.ignore(1000,'\n');
	getline(cin,nome);
	cout << "Ponto de Recolha (id): ";
	cin >> id;
	*casa = e->getMapa()->getPonto(id);

	if(casa->getID() == -1){
		throw PontoInexistente(*casa);
	}
	//so sao aceites pontos de recolha que s�o estao assinalados como pontos de recolha
	if(!e->getMapa()->isPontoInteresse(*casa))
		throw PontoRecolhaInvalido(*casa);

	casa->incNumCriancas(); //?? nao sei se deve estar aqui

	Cliente *c = new Cliente(nome,casa);
	if(!e->getIsEscola()){
		cout << "Morada Escolar (id): ";
		cin >> id;

		*escola = e->getMapa()->getPonto(id);
		if(escola->getID() == -1){
			throw PontoInexistente(*escola);
		}
		c->setNovaEscola(escola);
	}
	else
		c->setNovaEscola(e->getEndereco());

	if(e->addCliente(c) == false)
		throw ClienteJaExiste(nome,*escola,*casa);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void removerCliente(Empresa *e){
	int id;

	clrscr();
	displayTitulo("REMOVER CLIENTE");
	e->displayClientes();
	cout << "\nDigite o ID do cliente que quer remover: ";
	cin >> id;

	if(e->removeCliente(id) == false)
		throw ClienteInexistente(id);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void verClientes(Empresa *e){
	clrscr();
	displayTitulo("CLIENTES");
	e->displayClientes();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuClientes(Empresa *e){
	int op;
	do {
		clrscr();
		displayMenuClientes();
		opccao(op, 1, 5);
		switch (op) {
		case 1: { //add
			addCliente(e);
			break;
		}
		case 2: { //rem
			removerCliente(e);
			break;
		}
		case 3: {//ver
			verClientes(e);
			break;
		}
		case 4: {//pesq. traj
			throw VoltarAtras();
		}
		}
	} while (1);
}


//VEICULO
//==============================================================================================================

void addVeiculo(Empresa *e){
	string matricula;
	int num;
	//char classe;

	clrscr();
	displayTitulo("ADICIONAR VEICULO");
	cout << "Matricula: ";
	cin >> matricula;
	cout << "N�mero de lugares: ";
	cin >> num;

	Veiculo *v = new Veiculo(matricula, num);

	if(!e->addTransporte(v))
		throw VeiculoJaExiste(matricula);

	cout << endl;
	esperar();
	throw VoltarAtras();
}

void removerVeiculo(Empresa *e){
	string m;
	clrscr();
	displayTitulo("REMOVER VEICULO");
	e->displayVeiculos();
	cout << endl;
	cout << "Digite a matricula do veiculo: ";
	cin >> m;
	Veiculo * v = new Veiculo(m,0);
	if(!e->removeTransporte(v))
		throw VeiculoInexistente(m);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void verVeiculos(Empresa *e){
	clrscr();
	displayTitulo("VEICULOS");
	e->displayVeiculos();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void trajetoVeiculoIda(Empresa *e){

	e->distribuiCliVeiculos();

	string m;
	clrscr();
	displayTitulo("VER TRAJETO DO VEICULO");
	e->displayVeiculos();
	cout << endl;
	cout << "Digite a matricula do veiculo: ";
	cin >> m;
	if(!e->displayTrajetosIda(m))
		throw VeiculoInexistente(m);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void trajetoVeiculoVolta(Empresa *e){

	e->distribuiCliVeiculos();

	string m;
	clrscr();
	displayTitulo("VER TRAJETO DO VEICULO");
	e->displayVeiculos();
	cout << endl;
	cout << "Digite a matricula do veiculo: ";
	cin >> m;
	if(!e->displayTrajetosVolta(m))
		throw VeiculoInexistente(m);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuVeiculos(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuVeiculos();
		opccao(op, 1, 5);
		switch (op) {
		case 1: { //add
			addVeiculo(e);
			break;
		}
		case 2: { //rem
			removerVeiculo(e);
			break;
		}
		case 3: {//ver
			verVeiculos(e);
			break;
		}
		case 4: {//ver traj ida
			trajetoVeiculoIda(e);
			break;
		}
		case 5:{//ver traj volta
			trajetoVeiculoVolta(e);
			break;
		}
		case 6: {
			throw VoltarAtras();
		}
		}
	} while (1);
}
//PONTOS DE RECOLHA
//==============================================================================================================
void addPontoRecolha(Empresa *e){
	Morada ponto;
	int id;

	clrscr();
	displayTitulo("ADICIONAR PONTO DE RECOLHA");

	cout << "Morada Recolha (id): ";
	cin >> id;
	ponto = e->getMapa()->getPonto(id);

	if(ponto.getID() == -1){
		throw PontoInexistente(ponto);
	}

	if(!e->getMapa()->setPontoInteresse(ponto,true))
		throw PontoRecolhaInvalido(ponto);

	cout << endl;
	esperar();
	throw VoltarAtras();
}

void removerPontoRecolha(Empresa *e){
	Morada ponto;
	int id;

	clrscr();
	displayTitulo("REMOVER PONTO DE RECOLHA");

	e->displayPontosRecolha();

	cout << "Morada Recolha (id): ";
	cin >> id;
	ponto = e->getMapa()->getPonto(id);

	if(ponto.getID() == -1){
		throw PontoInexistente(ponto);
	}
	e->setClientesPI(ponto.getID());
	e->getMapa()->setPontoInteresse(ponto,false);
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void verPontosRecolha(Empresa *e){
	clrscr();
	displayTitulo("PONTOS DE RECOLHA");
	e->displayPontosRecolha();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuPontos(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuPI();
		opccao(op, 1, 5);
		switch (op) {
		case 1: { //ver escolas
			addPontoRecolha(e);
			break;
		}
		case 2: { //ver por alunos
			removerPontoRecolha(e);
			break;
		}
		case 3: {//ver
			verPontosRecolha(e);
			break;
		}
		case 4:{
			throw VoltarAtras();
		}
		}
	} while (1);
}
//Escolas
//==============================================================================================================
void verEscolas(Empresa * e){
	clrscr();
	displayTitulo("ESCOLAS");
	e->displayEscolas();
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void verAlunosEscolas(Empresa * e){
	clrscr();
	displayTitulo("ESCOLAS");
	vector<Cliente *> clientes;
	for (unsigned int i = 0; i < e->getEscolas().size(); ++i) {
		cout << "Escola - " << *e->getEscolas()[i] << endl;
		clientes = e->getClientesEscola(e->getEscolas()[i]);
		for (int j = 0; j < clientes.size(); ++j) {
			cout << *clientes[j] << endl;
		}
		cout << endl;
	}
	cout << endl;
	esperar();
	throw VoltarAtras();
}

void menuEscolas(Empresa *e){
	clrscr();
	int op;
	do {
		displayMenuEscolas();
		opccao(op, 1, 3);
		switch (op) {
		case 1: { //ver escolas
			verEscolas(e);
			break;
		}
		case 2: { //ver por alunos
			verAlunosEscolas(e);
			break;
		}
		case 3: {
			throw VoltarAtras();
		}
		}
	} while (1);
}

//==============================================================================================================
void opMenuInicial(Empresa *e, int op) {
	switch (op) {
	case 1: { //veiculos
		menuVeiculos(e);
		break;
	}
	case 2: { //clientes
		menuClientes(e);
		break;
	}
	case 3: {//trajetos
		menuPontos(e);
		break;
	}
	case 4: { //escolas
		menuEscolas(e);
		break;
	}
	case 5:{
		e->guardarInfo();
		break;
	}
	}
}

void menuInicial(Empresa *e) {
	int op;
	do {
		try {
			clrscr();
			displayMenuInicial(e->getNome());
			opccao(op, 1, 5);
			opMenuInicial(e, op);
		}
		catch (OpccaoInvalida<int>(x)) {
			cout << x.getOp() << " nao se encontra entre as opccoes "
					<< x.getMin() << " e " << x.getMax() << endl << endl;
			esperar();
		}
		catch (VoltarAtras) {
		}
		catch (InputFail) {
			cout << endl;
			esperar();
		}
		catch (ClienteJaExiste(e)){
			cout << "Nao foi possivel adicionar o cliente com nome " << e.getNome() << " ou morada escolar " << e.getMoradaEscola() << " e residencia "<< e.getMoradaResidencia() << ".\n";
			esperar();
		}

		catch ( ClienteInexistente(e)){
			cout << "Nao existe um cliente com o id " << e.getID() << endl;
			esperar();
		}

		catch (PontoInexistente(e)){
			cout << "Nao existe no mapa esse ponto\n";
			esperar();
		}
		catch (VeiculoJaExiste(e)){
			cout << "Ja existe um veiculo com a matricula " << e.getMatric()<< endl;
			esperar();
		}
		catch (VeiculoInexistente(e)){
			cout << "Nao existe um veiculo com a matricula " << e.getMatric()<< endl;
			esperar();
		}
		catch (ResidenciaInvalida(e)){
			cout << "A residencia " << e.getResidencia() << " nao pode ser uma escola\n";
			esperar();
		}
		catch (VeiculosInsuficientes()){
			cout << "Nao ha veiculos suficientes para o numero de clientes. Adicione um novo veiculo.\n";
			esperar();
		}
		catch(PontoRecolhaInvalido(e)){
			cout << "Nao existe um ponto de recolha " << e.getPonto() << endl;
			esperar();
		}
	} while (op != 5);
}

//Empresa
//==============================================================================================================
void menuEmpresa(Empresa *e){
	clrscr();
	int id;
	char resp;

	do {
		displayTitulo("EMPRESA - "+e->getNome());
		cout << "A empresa pertence a uma escola ? (S/N)\n";
		cin >> resp;
	}
	while(resp != 'S' && resp != 'N' && resp != 's' && resp != 'n');

	if(resp == 'S' || resp == 's')
		e->setIsEscola(true);
	else
		e->setIsEscola(false);

	e->carregarInfo();

	menuInicial(e);
}

int main(){

	Morada * source = new Morada(56,-0.159533,0.67583); 	// MUDAR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Empresa *e = new Empresa("Transportes Escolares",source);
	menuEmpresa(e);
	esperar();

	delete(e);
	return 0;
}
