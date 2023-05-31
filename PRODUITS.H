#ifndef PRODUITS_H
#define PRODUITS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_PRODUCT_NAME_LENGTH 50


typedef enum { SMALL, MEDIUM, LARGE } Size;

// Structure de données pour stocker les informations sur un produit
typedef struct {
  char product_name[MAX_NAME];
  int product_ref;
  int quantity;
  float price;
  Size t;
  int places;
} Product;

// Déclaration des fonctions liées aux produits

void add_product(Product *p);
// Modifie un produit existant à partir de sa référence
void modify_product(int product_ref);

// Supprime un produit à partir de sa référence
void remove_product(int ref_product);

// Affiche les informations de tous les produits
void display_product(const Product *product);
void display_all_products();

// Affiche les informations d'un produit en fonction de sa réference
void display_product_by_ref(int ref);

// Affiche les informations d'un produit en fonction de son nom
void display_product_by_name(const char *name);

// Augmentation des stocks
void increase_stock(int ref);

int load_products(Product products[]);

void display_products_with_zero_stock(Product products[], int numProducts);

void display_products_with_lowest_stock(Product products[], int numProducts, int numToDisplay);

int calculate_remaining_space(Product products[], int numProducts, int totalSpace);

void gestion_stock(Product products[], int numProducts, int totalSpace);



#endif /* PRODUITS_H */
