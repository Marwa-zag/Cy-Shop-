#ifndef CLIENTS_H
#define CLIENTS_H

#include "ACHATS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 100
#define MAX_HISTO 500
#define MAX_LINE 256
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME_LENGTH 50

// Structure de données pour stocker les informations sur un client
typedef struct {
  char client_name[MAX_NAME];
  char client_firstname[MAX_NAME];
  char date_of_birth[MAX_NAME];
  int client_id;
  int nb_purchases;
  float total_purchases;
  char purchases_history[MAX_HISTO];
} Client;

// Déclaration des fonctions liées aux clients
void add_client();
void modify_client();
void delete_client();
void display_client();
// Déclaration de la fonction chercher_client
Client find_client(char *client_name, char *client_firstname);

Client load_client(int client_id);
bool client_exists(int client_id);

#endif /* CLIENTS_H */
