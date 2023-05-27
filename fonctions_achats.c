#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_NAME 100
#define MAX_HISTO 500

void add_achat(const Client* c, const Achat a) {
  // Générer le nom du fichier avec l'extension .txt
  char filename[100];
  sprintf(filename, "%s.txt", c->client_name);

  // Ouvrir le fichier en mode "a" pour ajouter les achats à la fin du fichier existant ou créer un nouveau fichier s'il n'existe pas
  FILE* f = fopen(filename, "a");
  if (f == NULL) {
    printf("Erreur lors de la création du fichier d'achat pour le client '%s'.\n", c->client_name);
    return;
  }

  // Écrire l'achat dans le fichier
  fprintf(f, "Achat effectué :\n");
  fprintf(f, "Nom Produit: %s\nQuantité: %d\nPrix unitaire: %.2f\n\n", a.product_name, a.quantity, a.unit_price);

  // Écrire l'ID du client dans le fichier
  fprintf(f, "ID: %d\n\n", c->client_id);

  // Fermer le fichier
  fclose(f);

  printf("L'achat a été ajouté pour le client '%s'. Un nouveau fichier d'achat a été créé : %s\n", c->client_name, filename);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction supprime achat 

void delete_achat(const Client* c, const char* product_name) {
  // Générer le nom du fichier avec l'extension .txt
  char filename[100];
  sprintf(filename, "%s.txt", c->client_name);

  // Ouvrir le fichier en mode "r+" pour lecture et écriture
  FILE* f = fopen(filename, "r+");
  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier d'achats pour le client '%s'.\n", c->client_name);
    return;
  }

  // Créer un fichier temporaire pour stocker les achats sans l'achat à supprimer
  FILE* temp = fopen("temp.txt", "w");
  if (temp == NULL) {
    printf("Erreur lors de la création du fichier temporaire.\n");
    fclose(f);
    return;
  }

  // Parcourir les achats du client
  Achat current_purchase;
  int found = 0;
  while (fscanf(f, "Achat effectué :\nNom Produit: %[^\n]\nQuantité: %d\nPrix unitaire: %f\n\n", current_purchase.product_name, &current_purchase.quantity, &current_purchase.unit_price) == 3) {
    // Vérifier si l'achat correspond à celui que nous voulons supprimer
    if (strcmp(current_purchase.product_name, product_name) == 0) {
      found = 1;
      continue; // Ignorer l'achat à supprimer en ne l'écrivant pas dans le fichier temporaire
    }
    // Écrire les autres achats dans le fichier temporaire
    fprintf(temp, "Achat effectué :\nNom Produit: %s\nQuantité: %d\nPrix unitaire: %.2f\n\n", current_purchase.product_name, current_purchase.quantity, current_purchase.unit_price);
  }

  // Si l'achat n'a pas été trouvé, afficher un message d'erreur
  if (!found) {
    printf("L'achat de '%s' pour le client '%s' n'a pas été trouvé.\n", product_name, c->client_name);
  }

  // Fermer les fichiers
  fclose(f);
  fclose(temp);

  // Supprimer l'ancien fichier d'achats
  remove(filename);

  // Renommer le fichier temporaire avec le nom du fichier d'achats original
  rename("temp.txt", filename);

  printf("L'achat de '%s' pour le client '%s' a été supprimé.\n", product_name, c->client_name);
}


///////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction trouver achat ( a revoir ca ne marche pas )

Achat find_achat(const Client client, const int ref) {
    Achat achat;
    strcpy(achat.product_name, "");
    achat.quantity = 0;
    achat.unit_price = 0.0;

    printf("Quantité du produit [%d] pour le client [%s %s] : ", ref, client.client_firstname, client.client_name);
    scanf("%d", &achat.quantity);
    vider_buffer();
    printf("Prix unitaire du produit [%d] pour le client [%s %s] : ", ref, client.client_firstname, client.client_name);
    scanf("%f", &achat.unit_price);
    vider_buffer();

    // Ouvrir le fichier "produits.txt" en lecture
    FILE *produits_file = fopen("produits.txt", "r");
    if (produits_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier produits.txt.\n");
        return achat;
    }

    // Ouvrir le fichier du client en écriture en mode ajout (append)
    char client_file_name[MAX_NAME + 5];  // +5 pour ajouter ".txt" à la fin
    sprintf(client_file_name, "%s.txt", client.client_name);
    FILE *client_file = fopen(client_file_name, "a");
    if (client_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier du client %s.\n", client.client_name);
        fclose(produits_file);
        return achat;
    }

    // Parcourir le fichier "produits.txt" pour trouver le produit correspondant à la référence
    int found = 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), produits_file) != NULL) {
        int current_ref;
        char product_name[MAX_NAME];
        float price;

        // Lire la référence, le nom du produit et le prix du produit à partir de la ligne
        if (sscanf(line, "%d %[^\n] %f", &current_ref, product_name, &price) == 3) {
            if (current_ref == ref) {
                // Produit trouvé, écrire les détails dans le fichier du client
                fprintf(client_file, "Achat effectué :\n");
                fprintf(client_file, "Nom Produit: %s\n", product_name);
                fprintf(client_file, "Quantité: %d\n", achat.quantity);
                fprintf(client_file, "Prix unitaire: %.2f\n", achat.unit_price);
                fprintf(client_file, "\n");

                found = 1;
                break;
            }
        }
    }

    // Fermer les fichiers
    fclose(produits_file);
    fclose(client_file);

    if (!found) {
        printf("Produit avec la référence %d non trouvé dans le fichier produits.txt.\n", ref);
    }

    return achat;
}




///////////////////////////////////////////////////////////////////////////////////////////////////

// Affiche l'historique d'achat du client ( ca marche)

void display_achats(char client_name[]) {
  char name_fichier[50];
  sprintf(name_fichier, "%s.txt", client_name);
  FILE *f = fopen(name_fichier, "r");
  if (f == NULL) {
    printf(
        "Erreur lors de l'ouverture du fichier d'achats pour le client '%s'.\n",
        client_name);
    return;
  }

  printf("Client : %s\n", client_name);

  printf("%-20s %-10s %-15s\n", "Nom du produit", "Quantité", "Prix unitaire");

  char line[100];
  while (fgets(line, sizeof(line), f) != NULL) {
    if (strcmp(line, "Achat effectué :\n") == 0) {
      char product_name[50];
      int quantity;
      float unit_price;

      fgets(line, sizeof(line), f);  // Lire la ligne "Nom Produit: ..."
      sscanf(line, "Nom Produit: %[^:]:", product_name);

      fgets(line, sizeof(line), f);  // Lire la ligne "Quantité: ..."
      sscanf(line, "Quantité: %d", &quantity);

      fgets(line, sizeof(line), f);  // Lire la ligne "Prix unitaire: ..."
      sscanf(line, "Prix unitaire: %f", &unit_price);

      printf("%-20s %-10d %-15.2f\n", product_name, quantity, unit_price);

      // Ignorer la ligne contenant l'ID
      fgets(line, sizeof(line), f);
    }
  }

  fclose(f);
}



////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche les 3 derniers achats effectuer par le client 5 verifier
// si il prend en compte les acahts avec les espaces)

void display_three_last_achats(char client_name[]) {
  // Construire le nom du fichier d'achats
  char filename[MAX_NAME + 5]; // +5 pour ajouter ".txt" à la fin
  sprintf(filename, "%s.txt", client_name);

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

  // Variables pour stocker les 3 derniers achats
  char last_product_names[3][50];
  int last_quantities[3];
  float last_unit_prices[3];
  int nb_purchases_found = 0;

  // Lecture du contenu du fichier d'achats
  char line[100];
  while (fgets(line, sizeof(line), fichier_achats) != NULL) {
    if (strncmp(line, "Nom Produit:", 12) == 0) {
      sscanf(line, "Nom Produit: %[^\n]", product_name);
      fgets(line, sizeof(line), fichier_achats);
      sscanf(line, "Quantité: %d", &quantity);
      fgets(line, sizeof(line), fichier_achats);
      sscanf(line, "Prix unitaire: %f", &unit_price);

      // Stockage des informations de l'achat dans les tableaux
      strncpy(last_product_names[nb_purchases_found], product_name, sizeof(product_name));
      last_quantities[nb_purchases_found] = quantity;
      last_unit_prices[nb_purchases_found] = unit_price;

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
  printf("Les 3 derniers achats de %s :\n", client_name);
  for (i = nb_purchases_found - 1; i >= 0; i--) {
    printf("Produit : %s\n", last_product_names[i]);
    printf("Quantité : %d\n", last_quantities[i]);
    printf("Prix unitaire : %.2f\n", last_unit_prices[i]);
    printf("\n");
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche le montant total des achats (Verifier plus tard si ya le
// temps avec la date)

float calculate_total_amount_from_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erreur lors de l'ouverture du fichier d'achats.\n");
    return 0.0;
  }

  float total_amount = 0.0;
  char product_name[MAX_NAME];
  int quantity;
  float unit_price;

  // Lecture des achats du fichier et calcul du montant total
  while (fscanf(file, "%s %d %f", product_name, &quantity, &unit_price) == 3) {
    // Calcul du montant pour cet achat
    float amount = quantity * unit_price;
    total_amount += amount;
  }

  fclose(file);

  // Affichage du montant total des achats
  printf("Montant total des achats pour le client : %.2f\n", total_amount);

  return total_amount;
}

