# Sistema de Gerenciamento de Eventos Acadêmicos

## 1. Sobre o Projeto

Este projeto foi desenvolvido como trabalho final da disciplina **Estrutura de Dados I**, com o objetivo de aplicar conceitos como listas, filas, pilhas e algoritmos de ordenação.

O sistema permite cadastrar eventos, atividades e participantes, além de realizar check-in e desfazer remoções de forma dinâmica.

---

## 2. Estruturas de Dados Utilizadas

| Módulo         | Estrutura                 |
|----------------|---------------------------|
| Eventos        | Lista Encadeada Circular  |
| Atividades     | Lista Encadeada Simples   |
| Participantes  | Lista Duplamente Encadeada|
| Check-in       | Fila (FIFO)               |
| Desfazer       | Pilha (LIFO)              |
| Ordenações     | Merge Sort (horário), Bubble Sort (nome) |

---

## 3. Funcionalidades

- Cadastro e remoção de eventos
- Cadastro, listagem e ordenação de atividades
- Cadastro, listagem e ordenação de participantes
- Fila de check-in com histórico
- Desfazer remoções usando pilha

---

## 4. Estrutura de Pastas
```
ED1/
|
├── headers/
│    └── *.h
├── source/
│       └── *.c
```

---

## 5. Compilação e Execução

**Pré-requisitos:** gcc instalado

Ao iniciar o projeto, va para a pasta source com o terminal
```cd /source```
Com isso, voce pode iniciar a compilacao do projeto com o comando:
```
gcc *.c -o main
```
Com este comando o compilador ira rodar os arquivos .c , iniciando o sistema de gerenciamento de eventos.

---

## 6. Como Usar o Sistema

O sistema funciona por menus interativos no terminal. Ao iniciar o programa, o usuário vê o menu principal com as opções para gerenciar eventos, atividades, participantes, check-in ou desfazer uma ação.

Cada opção leva a um submenu:

- **Eventos:** permite cadastrar, listar e remover eventos  
- **Atividades:** após escolher um evento, permite cadastrar, listar, remover e ordenar atividades  
- **Participantes:** após escolher um evento e atividade, permite cadastrar, listar, remover e ordenar participantes  
- **Check-in:** permite realizar check-in, listar a fila, chamar o próximo e ver o histórico  
- **Desfazer:** desfaz a última remoção registrada  

As interações são feitas por número e exibidas no terminal.

---

## 7. Créditos

Desenvolvido por:

- Geovana Santos
- Kawan Dias
 - Mariany Aparecida 
 - Simão de Carvalho 


Disciplina: Estrutura de Dados I  
Universidade Federal do Piauí – UFPI  
Professor: [Leonardo Pio]

---
