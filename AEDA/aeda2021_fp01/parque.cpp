#include "parque.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :  lotacao(lot), numMaximoClientes(nMaxCli)
{
    vagas = lot;
}

unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (int i = 0; i < clientes.size(); ++i){
        if (clientes[i].nome == nome) return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size() < numMaximoClientes) {
        InfoCartao cliente;
        cliente.nome = nome;
        cliente.presente = false;
        clientes.push_back(cliente);
        return true;
    }
    return false;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    if (vagas <= 0) return false;
    for (size_t i = 0; i < clientes.size(); ++i){
        if (clientes.at(i).nome == nome) {
            if (clientes.at(i).presente) return false;
            clientes.at(i).presente = true;
            --vagas;
            return true;
        }
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    for (size_t i = 0; i < clientes.size(); ++i){
        if (clientes.at(i).nome == nome){
            if (clientes.at(i).presente) return false;
            clientes.erase(clientes.begin() + i);
            return true;
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string &nome) {
    for (size_t i = 0; i < clientes.size(); ++i){
        if (clientes.at(i).nome == nome){
            if (!clientes.at(i).presente) return false;
            clientes.at(i).presente = false;
            ++vagas;
            return true;
        }
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
return clientes.size();
}