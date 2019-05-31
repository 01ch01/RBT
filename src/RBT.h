/* File:   RBT.h
 * Author: ch
 * Created on 14 de Novembro de 2018, 15:12
 * Uma árvore rubro-negra é uma BST que insere e remove de forma inteligente,
 * para assegurar que a árvore permaneça aproximadamente balanceada. Tempo médio
 * de busca, inserção e remoção: O(log n). Altura máxima: 2*log(n+1). A raiz é
 * sempre preta; Toda folha (nil) é preta; Se um nó é vermelho, então seus
 * filhos são pretos;
 */
#include <iostream>
#include "Nodo.h"
#include "Pessoa.h"
using namespace std;
#ifndef RBT_H
#define RBT_H

class RBT {
 public:
  RBT();
  RBT(const RBT& orig);
  virtual ~RBT();

  void insert();
  void remove();

  void print();
  void inOrder();
  void postOrder();
  void preOrder();

  bool isEmpty();
  void insertAux(Nodo* no, Pessoa& claudio);
  void insertionRules(Nodo* no);

  void setRoot(Nodo* root);
  Nodo* getRoot() const;
  void setQuant(int quant);
  int getQuant() const;
  void setHeight(int height);
  int getHeight() const;

 private:
  Nodo* root;
  int quant, height;
};

#endif /* RBT_H */
