/* File:   RBT.cpp
 * Author: ch
 * Created on 14 de Novembro de 2018, 15:12 */

#include "../include/RBT.h"

RBT::RBT() {}

void RBT::setRoot(Nodo* root) {
  this->root = root;
}

Nodo* RBT::getRoot() const {
  return root;
}

void RBT::setQuant(int quant) {
  this->quant = quant;
}

int RBT::getQuant() const {
  return quant;
}

void RBT::setHeight(int height) {
  this->height = height;
}

int RBT::getHeight() const {
  return height;
}

RBT::RBT(const RBT& orig) {}

RBT::~RBT() {}

bool RBT::isEmpty() {
  if (this->quant == 0)
    return true;
  else
    return false;
}

/*Casos de inserção:
 * Caso 1 - Árvore vazia;
 * Caso 2 - Árvore sem tio (o root é o pai).
 * Caso 3 - Árvore com tio vermelho (recolorir pai, tio e avô);
 * Caso 4 - Árvore com tio preto (filho esquerdo e tio direito ou filho direito
 * e tio esquerdo); Caso 5 - Árvore com tio preto (filho esquerdo e tio esquerdo
 * ou filho direito e tio direito); Basicamente, quando o tio existe e é preto,
 * temos duas situações: Caso Left Left & Caso Right Right: Fazemos duas
 * rotações, o filho sobre o pai, o filho sobre o avô e depois recolorimos o
 * filho e o avô; Caso Left Right & Caso Right Left: Apenas uma rotação, o pai
 * rotaciona sobre o avô e recolorimos o pai e o avô.
 */

void RBT::insert() {
  Pessoa claudio;
  claudio.fill();
  Nodo* son = new Nodo(claudio);

  int result = claudio.comparacao(this->root->GetItem().getCpf());

  if (isEmpty() == true) {  // Caso 1
    this->root = son;
    son->SetDad(NULL);
    son->SetLeft(NULL);
    son->SetRight(NULL);
    son->SetColor(false);  // root é preto
    this->height++;
    this->quant++;

  } else if (this->root->GetLeft() == NULL ||
             this->root->GetRight() == NULL) {  // Caso 2 (sem tio)

    if (result == -1) {
      this->root->SetRight(son);  // filho à direita

    } else if (result == 1) {
      this->root->SetLeft(son);  // filho à esquerda

    } else if (result == 0) {
      cout << "\n\tERRO! Arquivos Duplicados!\n";
    }

    if (this->root->numberSons() ==
        1)  // a cada primogênito, a altura deve ser incrementada
      this->height++;

  } else {  // vamos aos tios, mas primeiro temos  que achar em que lugar vamos
            // inserir nosso novo elemento
    insertAux(this->root, claudio);
  }
}

void RBT::insertAux(Nodo* no, Pessoa& claudio) {
  int result = claudio.comparacao(no->GetItem().getCpf());

  if (result == -1) {  // caso ele seja menor que o root
    if (no->GetLeft() == NULL) {
      // insere o cara aqui e faz as devidas modificações (balanceamento)
      Nodo* son = new Nodo(claudio);
      no->SetLeft(son);
      son->SetDad(no);
      this->quant++;
      if (no->numberSons() == 1)
        this->height++;

      insertionRules(son);  // bora fazer as recolorações e rotações

    } else {
      insertAux(
          no->GetLeft(),
          claudio);  // se tem mais coisa, percorre até achar algum lugar vazio
    }

  } else if (result == 1) {  // caso ele seja maior que o root
    if (no->GetRight() == NULL) {
      // insere o cara aqui e faz as devidas modificações (balanceamento)
      Nodo* son = new Nodo(claudio);
      no->SetRight(son);
      son->SetDad(no);
      this->quant++;
      if (no->numberSons() == 1)
        this->height++;

      insertionRules(son);  // bora fazer as recolorações e rotações

    } else {
      insertAux(
          no->GetRight(),
          claudio);  // se tem mais coisa, percorre até achar algum lugar vazio
    }

  } else if (result == 0) {
    cout << "\n\tERRO! Arquivos Duplicados!\n";
  }
}

void RBT::insertionRules(Nodo* no) {
  // lembrando aqui que "no" é o filho, ok?

  Nodo* pai = no->GetDad();
  Nodo* avo = pai->GetDad();
  Nodo* tio;

  int result = pai->GetItem().comparacao(avo->GetItem().getCpf());

  // descobrindo o tio
  if (result == -1) {
    tio = avo->GetRight();

  } else if (result == 1) {
    tio = avo->GetLeft();

  } else if (result == 0) {
    cout << "\n\tERRO! Deu alguma duplicação ae, pq não deu pra instanciar o "
            "tio";
  }

  // agora sim vamos ao casos
  // Caso 3 - Árvore com tio vermelho (recolorir pai, tio e avô);
  if (tio->IsColor() == true) {
    pai->swapColor();
    tio->swapColor();
    avo->swapColor();

  } else {  // agora que fica complicado... -_-
    // Caso Left Right & Caso Right Left: Apenas uma rotação,
    // o pai rotaciona sobre o avô e recolorimos o pai e o avô.

    if ((avo->GetRight() == tio && pai->GetLeft() == no) ||
        (avo->GetLeft() == tio && pai->GetRight() == no)) {
      pai->SetDad(avo->GetDad());
      avo->SetDad(pai);
      pai->swapColor();
      avo->swapColor();

    }  // agora o Caso Left Left && Caso Right Right: Duas rotações, o filho
       // sobre o pai e o filho sobre o avô. Recolorir o filho e o avô
    else if ((avo->GetLeft() == tio && pai->GetLeft() == no) ||
             (avo->GetRight() == tio && pai->GetRight() == no)) {
      // rotacionando o fiho sobre o pai
      no->SetDad(pai->GetDad());
      pai->SetDad(no);

      // rotacionando o filho sobre o avô
      no->SetDad(avo->GetDad());
      avo->SetDad(no);

      no->swapColor();
      avo->swapColor();
    }
  }
}
