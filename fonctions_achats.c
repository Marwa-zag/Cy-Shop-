#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_NAME 100
#define MAX_HISTO 500
#define MAX_HISTO 500
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100
#define MAX_TAG 200

bool product_exists(int ref) {
  // Ouvrir le fichier des produits en mode lecture
  FILE *f = fopen("produits.txt", "r");
  if (f == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return false;
  }

  // Parcourir le fichier ligne par ligne
  char line[MAX_LINE];
  char reference[MAX_REF_LENGTH];
  while (fgets(line, sizeof(line), f)) {
    // Extraire la référence du produit de la ligne
    if (sscanf(line, "Référence: %s", reference) == 1) {
      int product_ref = atoi(reference);
      // Si la référence correspond à celle recherchée, le produit existe
      if (product_ref == ref) {
        fclose(f);
        return true;
      }
    }
  }

  // Fermer le fichier
  fclose(f);

  // Si la référence n'a pas été trouvée, le produit n'existe pas
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui recupere les donnes d'un produit

bool get_product_by_ref(int ref, Product *product) {
  FILE *f = fopen("produits.txt", "r");
  if (f == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return false;
  }

  char line[MAX_LINE];
  char tag[MAX_TAG];
  bool found = false;
  bool is_matching_product = false;
  bool has_name = false;  // Ajout de la variable pour le nom du produit

  while (fgets(line, sizeof(line), f)) {
    if (sscanf(line, "%[^:]: %[^\n]", tag, line) == 2) {
      if (strcmp(tag, "Référence") == 0) {
        int current_ref = atoi(line);
        if (current_ref == ref) {
          is_matching_product = true;
        } else {
          is_matching_product = false;
        }
      } else if (is_matching_product) {
        if (strcmp(tag, "Nom") == 0) {
          strncpy(product->product_name, line, MAX_NAME);
          has_name = true;  // Marquer la présence du nom du produit
        } else if (strcmp(tag, "Quantité en stock") == 0) {
          product->quantity = atoi(line);
        } else if (strcmp(tag, "Prix") == 0) {
          product->price = atof(line);
        } else if (strcmp(tag, "Taille") == 0) {
          product->t = atoi(line);
        }
        found = true;
      }
    }
  }
  fclose(f);

  if (!found) {
    printf("Erreur : le produit avec la référence %d n'a pas été trouvé.\n", ref);
    return false;
  }

  if (!has_name) {  // Vérifier si le nom du produit a été trouvé
    printf("Erreur : le nom du produit avec la référence %d n'a pas été trouvé.\n", ref);
    return false;
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui ajoute un achat dans le fichier d'un client 

void add_achat(const Client *c, const Achat a) {
    if (!client_exists(c->client_id)) {
        printf("Le client avec l'ID %d n'existe pas.\n", c->client_id);
        return;
    }

    if (!product_exists(a.product_ref)) {
        printf("Le produit avec la référence %d n'existe pas.\n", a.product_ref);
        return;
    }

    char filename[MAX_NAME];
    sprintf(filename, "%d_achats.txt", c->client_id);

    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        printf("Erreur lors de la création du fichier d'achat pour le client avec l'ID %d.\n", c->client_id);
        return;
    }

    Product product;
    if (!get_product_by_ref(a.product_ref, &product)) {
        printf("Erreur lors de la récupération des informations du produit avec la référence %d.\n", a.product_ref);
        fclose(f);
        return;
    }

    float price_total = product.price * a.quantity;
    int loyaltyPoints = calculateLoyaltyPoints(price_total); // Calcul des points de fidélité

    fprintf(f, "Achat effectué :\n");
    fprintf(f, "Nom Produit: %s\n", product.product_name);
    fprintf(f, "Quantité : %d\n", a.quantity);
    fprintf(f, "Prix unitaire: %.2f\n", product.price);
    fprintf(f, "Prix total: %.2f\n\n", price_total);
    fprintf(f, "Points de fidélité gagnés : %d\n\n", loyaltyPoints); // Ajout des points de fidélité

    fclose(f);

    printf("L'achat a été ajouté pour le client avec l'ID %d. Un nouveau fichier d'achat a été créé : %s\n", c->client_id, filename);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui calcule les points de fidelite 

int calculateLoyaltyPoints(float expense)
{
    // Chaque tranche de 5 unités de dépense donne 2 points de fidélité
    int points = (int)(expense / 5) * 2;
    return points;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Affiche l'historique d'achat du client

void display_achats(int client_id) {
  char name_fichier[50];
  sprintf(name_fichier, "%d_achats.txt", client_id);
  FILE *f = fopen(name_fichier, "r");
  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier d'achats pour le client avec l'ID %d.\n", client_id);
    return;
  }

  printf("Achats du client avec l'ID : %d\n", client_id);

  printf("%-20s %-10s %-15s\n", "Nom du produit", "Quantité", "Prix unitaire");

  char line[100];
  while (fgets(line, sizeof(line), f) != NULL) {
    if (strcmp(line, "Achat effectué :\n") == 0) {
      char product_name[50];
      int quantity;
      float unit_price;

      fgets(line, sizeof(line), f); // Lire la ligne "Nom Produit: ..."
      sscanf(line, "Nom Produit: %[^\n]", product_name);

      fgets(line, sizeof(line), f); // Lire la ligne "Quantité : ..."
      sscanf(line, "Quantité : %d", &quantity);

      fgets(line, sizeof(line), f); // Lire la ligne "Prix unitaire: ..."
      sscanf(line, "Prix unitaire: %f", &unit_price);

      printf("%-20s %-10d %-15.2f\n", product_name, quantity, unit_price);

      // Ignorer la ligne vide
      fgets(line, sizeof(line), f);
    }
  }

  fclose(f);
}


////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche les 3 derniers achats effectuer par le client 

void display_three_last_achats(int client_id) {
  // Construire le nom du fichier d'achats
  char filename[MAX_NAME + 5]; // +5 pour ajouter ".txt" à la fin
  sprintf(filename, "%d_achats.txt", client_id);

  // Ouverture du fichier d'achats en mode lecture de texte
  FILE *fichier_achats = fopen(filename, "r");
  if (fichier_achats == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier d'achats.\n");
    return;
  }

  // Variables pour stocker les informations des achats
  char product_name[50];
  int quantity;
  float unit_price;

  Achat last_purchases[3];
  int nb_purchases_found = 0;

  // Lecture du contenu du fichier d'achats
  char line[100];
  while (fgets(line, sizeof(line), fichier_achats) != NULL) {
    if (strncmp(line, "Nom Produit:", 12) == 0) {
      sscanf(line, "Nom Produit: %[^\n]", product_name);
      fgets(line, sizeof(line), fichier_achats);
      sscanf(line, "Quantité : %d", &quantity);
      fgets(line, sizeof(line), fichier_achats);
      sscanf(line, "Prix unitaire: %f", &unit_price);

      // Stockage des informations de l'achat dans la structure
      strncpy(last_purchases[nb_purchases_found].product_name, product_name, sizeof(product_name));
      last_purchases[nb_purchases_found].quantity = quantity;
      last_purchases[nb_purchases_found].unit_price = unit_price;

      nb_purchases_found++;
      if (nb_purchases_found >= 3) {
        break; // Sortir de la boucle une fois que 3 achats ont été trouvés
      }
    }
  }

  // Fermeture du fichier d'achats
  fclose(fichier_achats);

  // Affichage des 3 derniers achats (ou moins si moins de 3 achats)
  int i;
  printf("Les 3 derniers achats du client avec l'ID %d :\n", client_id);
  printf("+----------------------------------------+\n");
  printf("|  Produit         | Quantité |  Prix    |\n");
  printf("+----------------------------------------+\n");
  for (i = nb_purchases_found - 1; i >= 0; i--) {
    printf("| %-16s| %-9d| $ %-7.2f|\n", last_purchases[i].product_name, last_purchases[i].quantity, last_purchases[i].unit_price);
    printf("+----------------------------------------+\n");
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Fonction pour la livraison (ne fonctionne pas)

//void livraison(Produit produits[], int nbProduits) {
    //char ref[MAX_REF];
    //int quantiteLivree;

    //printf("Saisir la référence du produit à livrer :\n");
    //scanf("%s", ref);
    //vider_buffer();

    // Recherche du produit dans le stock
    //int index = -1;
    //for (int i = 0; i < nbProduits; i++) {
        //if (strcmp(ref, produits[i].ref) == 0) {
            //index = i;
            //break;
        //}
    //}

    //if (index == -1) {
        //printf("Le produit avec la référence %s n'existe pas dans le stock.\n", ref);
        //return;
    //}

    //printf("Saisir la quantité à livrer :\n");
    //scanf("%d", &quantiteLivree);
    //vider_buffer();

    // Mise à jour de la quantité du produit dans le stock
    //produits[index].quantite += quantiteLivree;

    //printf("La livraison de %d unité(s) du produit %s (ref: %s) a été effectuée avec succès.\n", quantiteLivree, produits[index].nom, produits[index].ref);
//}

