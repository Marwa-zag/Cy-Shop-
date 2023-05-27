#ifndef ACHATS_H
#define ACHATS_H

#include "CLIENTS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME_LENGTH 50

// Structure de données pour stocker les informations sur un achat
typedef struct {
  char product_name[50];
  int quantity;
  float unit_price;
} Achat;

// Déclaration des fonctions liées aux achats
void add_achat(const Client* c, const Achat a);
;
void delete_achat(const Client* c, const char* product_name);
Achat find_achat(const Client client, const int ref);
void display_achats(char client_name[]);
void display__three_last_achats(char client_name[]);
float calculate_total_amount_from_file(const char* filename);
void management_mode();
void purchase_mode();

#endif /* ACHATS_H */
