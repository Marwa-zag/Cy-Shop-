#ifndef ACHATS_H
#define ACHATS_H

#include "CLIENTS.H"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
  int product_ref;
  int quantity;
  float unit_price;
} Achat;

bool product_exists(int ref);
// Déclaration des fonctions liées aux achats
void add_achat(const Client* c, const Achat a);
;
int calculateLoyaltyPoints(float expense);
void delete_achat(int client_id, const char* product_name) ;
void display_achats(int client_id);
void display_three_last_achats(int client_id);
void management_mode();
void purchase_mode();

#endif /* ACHATS_H */
