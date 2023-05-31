#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h> // Inclut le fichier d'en-tête pour le type bool
#define MAX_NAME 100
#define MAX_HISTO 500

// Fonction ajoute_client

void add_client() {
  FILE *fichier_clients;
  Client client;

  // Saisie des informations du client à ajouter
  printf("Saisissez les informations du client à ajouter :\n");
  printf("Nom : ");
  fgets(client.client_name, sizeof(client.client_name), stdin);
  vider_buffer();
  printf("Prénom : ");
  fgets(client.client_firstname, sizeof(client.client_firstname), stdin);
  vider_buffer();
  printf("ID : ");
  scanf("%d", &client.client_id);
  vider_buffer();
  printf("Date de naissance (JJ/MM/AAAA) : ");
  scanf("%s", client.date_of_birth);
  vider_buffer();

  // Suppression des caractères de nouvelle ligne
  client.client_name[strcspn(client.client_name, "\n")] = '\0';
  client.client_firstname[strcspn(client.client_firstname, "\n")] = '\0';

  // Création du nom de fichier unique pour le client
  char filename[MAX_NAME + MAX_NAME + 5]; // Nom du fichier = ID + ".txt"
  snprintf(filename, sizeof(filename), "%d.txt", client.client_id);

  // Ouverture du fichier en mode écriture
  fichier_clients = fopen(filename, "w");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_clients == NULL) {
    printf("Erreur : impossible de créer le fichier pour le client.\n");
    return;
  }

  // Écriture des informations du client dans le fichier
  fprintf(fichier_clients,
          "Nom: %s\nPrénom: %s\nID: %d\nDate de naissance: %s\n",
          client.client_name, client.client_firstname, client.client_id,
          client.date_of_birth);

  // Fermeture du fichier
  fclose(fichier_clients);

  printf("Le client a été ajouté avec succès !\n");
}

//////////////////////////////////////////////////// Verifie si le compte existe ou pas 

bool client_exists(int client_id) {
  FILE *fichier_clients;
  char filename[MAX_NAME + 5]; // Nom du fichier = ID + ".txt"
  snprintf(filename, sizeof(filename), "%d.txt", client_id);

  // Ouverture du fichier en mode lecture
  fichier_clients = fopen(filename, "r");

  if (fichier_clients != NULL) {
    // Le fichier existe, donc le client existe
    fclose(fichier_clients);
    return true;
  }

  // Le fichier n'existe pas, donc le client n'existe pas
  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Peut modifier les donnees du compte

void modify_client() {
  int client_id;
  char client_filename[MAX_NAME + 5]; // Nom du fichier du client à modifier
  char new_client_filename[MAX_NAME + 5]; // Nouveau nom du fichier du client
  FILE *fichier_client; // Pointeur vers le fichier du client
  Client client; // Variable pour stocker les informations du client

  // Demande de l'ID du client à modifier
  printf("ID du client à modifier : ");
  scanf("%d", &client_id);
  vider_buffer();

  // Génération du nom du fichier avec l'ID du client
  snprintf(client_filename, sizeof(client_filename), "%d.txt", client_id);

  // Ouverture du fichier en mode lecture
  fichier_client = fopen(client_filename, "r");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_client == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier du client.\n");
    return;
  }

  // Lecture des informations du client à partir du fichier
  fscanf(fichier_client, "Nom: %[^\n]\n", client.client_name);
  fscanf(fichier_client, "Prénom: %[^\n]\n", client.client_firstname);
  fscanf(fichier_client, "ID: %d\n", &client.client_id);
  fscanf(fichier_client, "Date de naissance: %[^\n]\n", client.date_of_birth);

  // Fermeture du fichier
  fclose(fichier_client);

  // Affichage des informations actuelles du client
  printf("Informations actuelles du client :\n");
  printf("Nom : %s\n", client.client_name);
  printf("Prénom : %s\n", client.client_firstname);
  printf("ID : %d\n", client.client_id);
  printf("Date de naissance : %s\n", client.date_of_birth);

  // Saisie des nouvelles informations pour le client
  printf("Nouveau nom du client : ");
  fgets(client.client_name, sizeof(client.client_name), stdin);
  client.client_name[strcspn(client.client_name, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
  printf("Nouveau prénom du client : ");
  fgets(client.client_firstname, sizeof(client.client_firstname), stdin);
  client.client_firstname[strcspn(client.client_firstname, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne
  printf("Nouvelle date de naissance (JJ/MM/AAAA) : ");
  fgets(client.date_of_birth, sizeof(client.date_of_birth), stdin);
  client.date_of_birth[strcspn(client.date_of_birth, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

  // Génération du nouveau nom de fichier avec l'ID du client
  snprintf(new_client_filename, sizeof(new_client_filename), "%d.txt", client_id);

  // Renommage du fichier avec le nouveau nom
  if (rename(client_filename, new_client_filename) != 0) {
    printf("Erreur : impossible de renommer le fichier du client.\n");
    return;
  }

  // Ouverture du fichier renommé en mode écriture
  fichier_client = fopen(new_client_filename, "w");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_client == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier du client.\n");
    return;
  }

  // Écriture des nouvelles informations du client dans le fichier
  fprintf(fichier_client,
          "Nom: %s\nPrénom: %s\nID: %d\nDate de naissance: %s\n",
          client.client_name, client.client_firstname, client.client_id,
          client.date_of_birth);

  // Fermeture du fichier
  fclose(fichier_client);

  printf("Le client a été modifié avec succès.\n");
}


/////////////////////////////////////////////////
////////////////////////////////////////////////

// Fonction qui supprime le compte d'un client

void delete_client() {
  int client_id;
  char client_filename[MAX_NAME + 5]; // Nom du fichier du client à supprimer
  FILE *fichier_clients;

  // Demande de l'ID du client à supprimer
  printf("ID du client à supprimer : ");
  scanf("%d", &client_id);
  vider_buffer();

  // Génération du nom du fichier avec l'ID du client
  snprintf(client_filename, sizeof(client_filename), "%d.txt", client_id);

  // Vérification si le fichier existe
  if (access(client_filename, F_OK) == -1) {
    printf("Erreur : le fichier du client n'existe pas.\n");
    return;
  }

  // Affichage du nom du fichier à supprimer
  printf("Le fichier du client à supprimer est : %s\n", client_filename);

  // Demande de confirmation de suppression
  printf("Êtes-vous sûr de vouloir supprimer ce fichier ? (O/N) : ");
  char confirmation;
  scanf(" %c", &confirmation);
  vider_buffer();

  if (confirmation == 'O' || confirmation == 'o') {
    // Suppression du fichier
    if (remove(client_filename) != 0) {
      printf("Erreur : impossible de supprimer le fichier du client.\n");
      return;
    }

    printf("Le fichier du client a été supprimé avec succès.\n");
  } else {
    printf("La suppression du fichier du client a été annulée.\n");
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui affiche un client

void display_client() {
  FILE *fichier_clients;
  int client_id;
  char client_filename[MAX_NAME + 5];
  char line[MAX_NAME + MAX_NAME + MAX_HISTO + 15]; // Variable temporaire pour lire une ligne du fichier

  // Demande de l'ID du client à afficher
  printf("ID du client à afficher : ");
  scanf("%d", &client_id);
  vider_buffer();

  // Génération du nom du fichier avec l'ID du client
  snprintf(client_filename, sizeof(client_filename), "%d.txt", client_id);

  // Ouverture du fichier en mode lecture
  fichier_clients = fopen(client_filename, "r");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_clients == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier du client.\n");
    return;
  }

  // Affichage des informations du client
  printf("Informations du client :\n");
  while (fgets(line, sizeof(line), fichier_clients)) {
    printf("%s", line);
  }

  // Fermeture du fichier
  fclose(fichier_clients);
}


///////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction chercher client ( a revoir si ca marche)

Client find_client(char *client_name, char *client_firstname) {
  char filename[MAX_NAME + MAX_NAME +
                5]; // Nom du fichier = nom + prénom + ".txt"
  FILE *fichier_client;
  Client client_found;

  // Création du nom de fichier unique pour le client
  snprintf(filename, sizeof(filename), "%s_%s.txt", client_name,
           client_firstname);

  // Ouverture du fichier en mode lecture
  fichier_client = fopen(filename, "r");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_client == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier du client.\n");
    client_found.client_name[0] =
        '\0'; // Retourne un client vide si erreur d'ouverture de fichier
    return client_found;
  }

  // Lecture des informations du client à partir du fichier
  fscanf(fichier_client, "Nom: %s\nPrénom: %s\nHistorique des achats: %[^\n]",
         client_found.client_name, client_found.client_firstname,
         client_found.purchases_history);

  // Fermeture du fichier
  fclose(fichier_client);

  // Retourne le client trouvé
  return client_found;
}

////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui recupere les informations d'un client a partir de son ID

Client load_client(int client_id) {
  FILE *fichier_clients = fopen("clients.txt", "r");
  if (fichier_clients == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier des clients.\n");
    Client empty_client;         // Client vide en cas d'erreur
    empty_client.client_id = -1; // Valeur d'identifiant invalide
    return empty_client;
  }

  Client client;
  int found = 0;

  while (fread(&client, sizeof(Client), 1, fichier_clients) == 1) {
    if (client.client_id == client_id) {
      found = 1;
      break;
    }
  }

  fclose(fichier_clients);

  if (!found) {
    printf("Erreur : client introuvable.\n");
    Client empty_client;         // Client vide en cas de non correspondance
    empty_client.client_id = -1; // Valeur d'identifiant invalide
    return empty_client;
  }

  return client;
}
