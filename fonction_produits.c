#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
#define MAX_NAME 100
#define MAX_HISTO 500
#define MAX_NAME 100
#define MAX_LINE 256
#define MAX_LINE_LENGTH 200
#define MAX_REF_LENGTH 10
#define MAX_PRODUCTS 100

void vider_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void add_product(Product *p) {
  FILE *fichier_produits;

  // Ouverture du fichier en mode ajout
  fichier_produits = fopen("produits.txt", "a");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_produits == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return;
  }

  // Saisie des informations du produit à ajouter
  printf("Saisissez les informations du produit à ajouter :\n");
  printf("Nom : ");
  scanf(" %[^\n]", p->product_name);
  vider_buffer();
  printf("Ref produit: ");
  scanf("%d", &p->product_ref); // Doit avoir 4 chiffres
  vider_buffer();
  printf("Quantite: ");
  scanf("%d", &p->quantity);
  vider_buffer();
  printf("Prix : ");
  scanf("%f", &p->price);
  vider_buffer();
  printf("Taille (0 pour SMALL, 1 pour MEDIUM, 2 pour LARGE) : ");
  int size;
  scanf("%d", &size);
  p->t = (Size)size;

  // Écriture des informations du produit dans le fichier
  fprintf(fichier_produits,
          "Nom: %s\nRéférence: %d\nQuantité en stock: %d\nPrix: %.2f\nTaille: "
          "%d\n\n",
          p->product_name, p->product_ref, p->quantity, p->price, p->t);

  // Fermeture du fichier
  fclose(fichier_produits);

  printf("Le produit a été ajouté avec succès !\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction modifie_produit

void modify_product(int product_ref) {
  FILE *file;
  FILE *temp_file;
  Product product;
  int found = 0;

  // Ouverture du fichier en mode lecture
  file = fopen("produits.txt", "r");
  if (file == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return;
  }

  // Création d'un fichier temporaire pour écrire les modifications
  temp_file = fopen("temp.txt", "w");
  if (temp_file == NULL) {
    printf("Erreur : impossible de créer le fichier temporaire.\n");
    fclose(file);
    return;
  }

  // Lecture des produits existants et écriture des modifications dans le
  // fichier temporaire
  while (fscanf(file,
                "Nom: %[^\n]\nRéférence: %d\nQuantité en stock: %d\nPrix: "
                "%f\nTaille: %d\n\n",
                product.product_name, &product.product_ref, &product.quantity,
                &product.price, &product.t) == 5) {
    if (product.product_ref == product_ref) {
      // Le produit a été trouvé, on demande les nouvelles informations à
      // l'utilisateur
      printf("Modifiez les informations du produit :\n");
      printf("Nom du produit: ");
      scanf(" %[^\n]", product.product_name);
      vider_buffer();
      printf("Quantité: ");
      scanf("%d", &product.quantity);
      vider_buffer();
      printf("Prix : ");
      scanf("%f", &product.price);
      vider_buffer();
      printf("Taille : ");
      scanf("%d", &product.t);
      vider_buffer();
      found = 1;
    }

    // Écriture du produit dans le fichier temporaire
    fprintf(temp_file,
            "Nom: %s\nRéférence: %d\nQuantité en stock: %d\nPrix: "
            "%.2f\nTaille: %d\n\n",
            product.product_name, product.product_ref, product.quantity,
            product.price, product.t);
  }

  fclose(file);
  fclose(temp_file);

  // Suppression de l'ancien fichier des produits
  remove("produits.txt");

  // Renommage du fichier temporaire en tant que fichier des produits
  rename("temp.txt", "produits.txt");

  if (found) {
    printf("Le produit a été modifié avec succès !\n");
  } else {
    printf("Erreur : le produit avec la référence %d n'a pas été trouvé.\n",
           product_ref);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction supprime_produit

void remove_product(int ref_product) {
  FILE *fp_in, *fp_out;
  Product p;
  int found = 0;

  // Ouverture du fichier des produits en mode lecture
  fp_in = fopen("produits.txt", "r");
  if (fp_in == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return;
  }

  // Création d'un fichier temporaire en mode écriture
  fp_out = fopen("produits.tmp", "w");
  if (fp_out == NULL) {
    printf("Erreur : impossible de créer le fichier temporaire.\n");
    fclose(fp_in);
    return;
  }

  // Parcours du fichier des produits
  while (fscanf(fp_in,
                "Nom: %[^\n]\nRéférence: %d\nQuantité en stock: %d\nPrix: "
                "%f\nTaille: %d\n\n",
                p.product_name, &p.product_ref, &p.quantity, &p.price,
                &p.t) == 5) {
    if (p.product_ref == ref_product) {
      found = 1; // Indique que le produit a été trouvé
    } else {
      // Écriture des produits non supprimés dans le fichier temporaire
      fprintf(fp_out,
              "Nom: %s\nRéférence: %d\nQuantité en stock: %d\nPrix: "
              "%.2f\nTaille: %d\n\n",
              p.product_name, p.product_ref, p.quantity, p.price, p.t);
    }
  }

  // Fermeture des fichiers
  fclose(fp_in);
  fclose(fp_out);

  // Suppression du fichier des produits original
  remove("produits.txt");

  // Renommage du fichier temporaire en tant que fichier des produits
  rename("produits.tmp", "produits.txt");

  // Affichage du message de succès ou d'erreur
  if (found) {
    printf("Le produit avec le numéro de référence %d a été supprimé avec succès.\n",
           ref_product);
  } else {
    printf("Le produit avec le numéro de référence %d n'existe pas.\n",
           ref_product);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction affiche_produit

void display_product(const Product *product) {
  printf("Nom: %s\n", product->product_name);
  printf("Référence: %d\n", product->product_ref);
  printf("Quantité en stock: %d\n", product->quantity);
  printf("Prix: %.2f\n", product->price);
  printf("Taille: %d\n", product->t);
}
///////////////////////////////////////////////
///////////////////////////////////////////////


void display_all_products() {
  FILE *fp;
  char line[MAX_LINE];
  Product product;

  // Ouverture du fichier des produits en mode lecture
  fp = fopen("produits.txt", "r");
  if (fp == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return;
  }

  printf("Affichage de tous les produits :\n");

  // Parcours du fichier des produits ligne par ligne
  while (fgets(line, MAX_LINE, fp) != NULL) {
    if (strncmp(line, "Nom: ", 5) == 0) {
      // Extraction du nom du produit à partir de la ligne
      strncpy(product.product_name, line + 5, MAX_NAME - 1);
      product.product_name[MAX_NAME - 1] = '\0';

      // Lecture des informations supplémentaires du produit depuis les lignes suivantes
      fgets(line, MAX_LINE, fp);
      sscanf(line, "Référence: %d", &product.product_ref);

      fgets(line, MAX_LINE, fp);
      sscanf(line, "Quantité en stock: %d", &product.quantity);

      fgets(line, MAX_LINE, fp);
      sscanf(line, "Prix: %f", &product.price);

      fgets(line, MAX_LINE, fp);
      sscanf(line, "Taille: %d", &product.t);

      // Affichage du produit
      display_product(&product);
      printf("\n");
    }
  }

  // Fermeture du fichier
  fclose(fp);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche en fonction de la ref

void display_product_by_ref(int ref) {
  FILE *fp;
  Product product;

  // Ouverture du fichier des produits en mode lecture avec encodage UTF-8
  fp = fopen("produits.txt", "r, ccs=UTF-8");
  if (fp == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return;
  }

  printf("Affichage du produit avec référence %d :\n", ref);

  // Parcours du fichier des produits
  while (fscanf(fp, "Nom: %[^\n]\n", product.product_name) != EOF) {
    // Lecture des informations du produit depuis le fichier
    fscanf(fp, "Référence: %d\n", &product.product_ref);
    fscanf(fp, "Quantité en stock: %d\n", &product.quantity);
    fscanf(fp, "Prix: %f\n", &product.price);
    fscanf(fp, "Taille: %d\n", &product.t);

    // Vérification si la référence du produit correspond à celle recherchée
    if (product.product_ref == ref) {
      // Affichage du produit
      display_product(&product);
      printf("\n");
      break;
    }
  }

  // Fermeture du fichier
  fclose(fp);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche en fonction du nom

void display_product_by_name(const char *name) {
  FILE *fp;
  Product product;
  char line[MAX_LINE];

  // Ouverture du fichier des produits en mode lecture avec encodage UTF-8
  fp = fopen("produits.txt", "r, ccs=UTF-8");
  if (fp == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des produits.\n");
    return;
  }

  printf("Affichage des produits avec le nom '%s' :\n", name);

  // Parcours du fichier des produits
  while (fgets(line, MAX_LINE, fp) != NULL) {
    if (strncmp(line, "Nom: ", 5) == 0) {
      // Extraction du nom du produit
      sscanf(line, "Nom: %[^\n]", product.product_name);

      // Vérification si le nom correspond à celui recherché
      if (strcmp(product.product_name, name) == 0) {
        // Extraction des autres informations du produit
        fgets(line, MAX_LINE, fp);
        sscanf(line, "Référence: %d", &product.product_ref);

        fgets(line, MAX_LINE, fp);
        sscanf(line, "Quantité en stock: %d", &product.quantity);

        fgets(line, MAX_LINE, fp);
        sscanf(line, "Prix: %f", &product.price);

        fgets(line, MAX_LINE, fp);
        sscanf(line, "Taille: %d", &product.t);

        // Affichage du produit
        display_product(&product);
        printf("\n");
      }
    }
  }

  // Fermeture du fichier
  fclose(fp);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui augmente le stock 

void increase_stock(int ref_product) {
  FILE *fp_in;
  FILE *fp_out;
  Product p;

  // Ouverture des fichiers d'entrée et de sortie
  fp_in = fopen("produits.txt", "r");
  fp_out = fopen("produits.tmp", "w");

  // Vérification de l'ouverture des fichiers
  if (fp_in == NULL || fp_out == NULL) {
    printf("Erreur : impossible d'ouvrir les fichiers des produits.\n");
    return;
  }

  // Parcours du fichier des produits
  while (fscanf(fp_in, "%[^\n]%*c", p.product_name) == 1 &&
         fscanf(fp_in, "Référence: %d\n", &p.product_ref) == 1 &&
         fscanf(fp_in, "Quantité en stock: %d\n", &p.quantity) == 1 &&
         fscanf(fp_in, "Prix: %f\n", &p.price) == 1 &&
         fscanf(fp_in, "Taille: %d\n", &p.t) == 1 && fscanf(fp_in, "\n") == 0) {

    if (p.product_ref != ref_product) {
      // Écriture des informations du produit dans le fichier de sortie
      fprintf(fp_out, "%s\n", p.product_name);
      fprintf(fp_out, "Référence: %d\n", p.product_ref);
      fprintf(fp_out, "Quantité en stock: %d\n", p.quantity);
      fprintf(fp_out, "Prix: %.2f\n", p.price);
      fprintf(fp_out, "Taille: %d\n", p.t);
      fprintf(fp_out, "\n");
    } else {
      int additional_quantity;
      printf("Veuillez saisir la quantité à ajouter au stock : ");
      scanf("%d", &additional_quantity);
      vider_buffer();

      // Mise à jour de la quantité du produit
      p.quantity += additional_quantity;

      // Écriture des informations du produit modifié dans le fichier de sortie
      fprintf(fp_out, "%s\n", p.product_name);
      fprintf(fp_out, "Référence: %d\n", p.product_ref);
      fprintf(fp_out, "Quantité en stock: %d\n", p.quantity);
      fprintf(fp_out, "Prix: %.2f\n", p.price);
      fprintf(fp_out, "Taille: %d\n", p.t);
      fprintf(fp_out, "\n");
    }
  }

  // Fermeture des fichiers
  fclose(fp_in);
  fclose(fp_out);

  // Suppression du fichier d'origine et renommage du fichier de sortie
  remove("produits.txt");
  rename("produits.tmp", "produits.txt");
}


////////////////////////////////////////////////////////////////////////////////////////////////////

// Récupere les informations du produits

int load_products(Product products[]) {
  FILE *fp;
  int numProducts = 0;
  char line[MAX_LINE_LENGTH];

  // Ouverture du fichier produits.txt en mode lecture
  fp = fopen("produits.txt", "r");
  if (fp == NULL) {
    printf("Erreur lors de l'ouverture du fichier produits.txt.\n");
    return 0;
  }

  // Lecture des lignes du fichier et extraction des informations des produits
  while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
    if (sscanf(line, "Nom: %[^\n]\nRéférence: %d\nQuantité en stock: %d\nPrix: %f\nTaille: %d\n",
               products[numProducts].product_name,
               &products[numProducts].product_ref,
               &products[numProducts].quantity,
               &products[numProducts].price,
               &products[numProducts].places) == 5) {
      numProducts++;
    }
  }

  // Fermeture du fichier
  fclose(fp);
  return numProducts;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

// Affiche les produits dont les stocks sont égale à 0

void display_products_with_zero_stock(Product products[], int numProducts) {
  int i;
  int found = 0;

  // Parcours des produits et affichage de ceux avec un stock inférieur ou égal à 5
  printf("Produits avec un stock de 0 ou inférieur à 5 :\n");
  for (i = 0; i < numProducts; i++) {
    if (products[i].quantity <= 5) {
      printf("Nom: %s\nRéférence: %d\nQuantité en stock: %d\nPrix: %.2f\nTaille: %d\n\n",
             products[i].product_name, products[i].product_ref, products[i].quantity,
             products[i].price, products[i].places);
      found = 1;
    }
  }

  // Affichage d'un message si aucun produit correspondant n'a été trouvé
  if (!found) {
    printf("Aucun produit avec un stock de 0 ou inférieur à 5.\n");
  }
}


void display_products_with_lowest_stock(Product products[], int numProducts, int numToDisplay) {
  int i, j;
  Product temp;
  int found = 0;

  if (numToDisplay > numProducts || numToDisplay <= 0) {
    printf("Veuillez spécifier un nombre valide de produits à afficher.\n");
    return;
  }

  // Trier les produits par ordre croissant de stock
  for (i = 0; i < numProducts - 1; i++) {
    for (j = 0; j < numProducts - i - 1; j++) {
      if (products[j].quantity > products[j + 1].quantity) {
        temp = products[j];
        products[j] = products[j + 1];
        products[j + 1] = temp;
      }
    }
  }

  // Affichage des produits avec les stocks les plus bas
  printf("Produits avec les stocks les plus bas :\n");
  for (i = 0; i < numProducts && found < numToDisplay; i++) {
    if (products[i].quantity > 0) {
      printf("Nom: %s\nRéférence: %d\nQuantité en stock: %d\nPrix: %.2f\nTaille: %d\n\n",
             products[i].product_name, products[i].product_ref, products[i].quantity,
             products[i].price, products[i].places);
      found++;
    }
  }

  if (found == 0) {
    printf("Aucun produit avec un stock supérieur à 0 trouvé.\n");
  }
}

int calculate_remaining_space(Product products[], int numProducts, int totalSpace) {
  int i;
  int usedSpace = 0;

  // Calcul de l'espace utilisé par les produits
  for (i = 0; i < numProducts; i++) {
    usedSpace += products[i].places * products[i].quantity; // Prendre en compte le stock
  }

  return totalSpace - usedSpace;
}

void gestion_stock(Product products[], int numProducts, int totalSpace) {
  // Appel des fonctions pour afficher les produits avec un stock de 0 ou inférieur à 5
  // et les produits avec les stocks les plus bas
  display_products_with_zero_stock(products, numProducts);

  // Modification ici: ajustement du nombre de produits à afficher
  int numToDisplay = (numProducts < 5) ? numProducts : 5;
  display_products_with_lowest_stock(products, numProducts, numToDisplay);

  // Calcul et affichage de l'espace restant en magasin
  int remainingSpace =
      calculate_remaining_space(products, numProducts, totalSpace);
  printf("Place restante en magasin : %d\n", remainingSpace);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

