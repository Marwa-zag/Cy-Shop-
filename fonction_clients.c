#include "ACHATS.H"
#include "CLIENTS.H"
#include "PRODUITS.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_NAME 100
#define MAX_HISTO 500

// Fonction ajouter_client

void add_client() {
    FILE* fichier_clients;
    Client client;

    // Saisie des informations du client à ajouter
    printf("Saisissez les informations du client à ajouter :\n");
    printf("Nom : ");
    scanf("%s", client.client_name);
    vider_buffer();
    printf("Prénom : ");
    scanf("%s", client.client_firstname);
    vider_buffer();
    printf("ID : ");
    scanf("%d", &client.client_id);
    vider_buffer();
    printf("Date de naissance (JJ/MM/AAAA) : ");
    scanf("%s", client.date_of_birth);
    vider_buffer();

    // Création du nom de fichier unique pour le client
    char filename[MAX_NAME + MAX_NAME + 5]; // Nom du fichier = nom + prénom + ".txt"
    snprintf(filename, sizeof(filename), "%s_%s.txt", client.client_name, client.client_firstname);

    // Ouverture du fichier en mode écriture
    fichier_clients = fopen(filename, "w");

    // Vérification si l'ouverture du fichier a réussi
    if (fichier_clients == NULL) {
        printf("Erreur : impossible de créer le fichier pour le client.\n");
        return;
    }

    // Écriture des informations du client dans le fichier
    fprintf(fichier_clients, "Nom: %s\nPrénom: %s\nID: %d\nDate de naissance: %s\n",
            client.client_name, client.client_firstname, client.client_id, client.date_of_birth);

    // Fermeture du fichier
    fclose(fichier_clients);

    printf("Le client a été ajouté avec succès !\n");
}



//////////////////////////////////////////////////////////////////////////////////////////////////////(
/// a revoir il ne prend pas les espaces)

void modify_client() {
  char client_filename[MAX_NAME + MAX_NAME + 5]; // Nom du fichier du client à modifier
  char new_client_filename[MAX_NAME + MAX_NAME + 5]; // Nouveau nom du fichier du client
  FILE* fichier_client; // Pointeur vers le fichier du client
  Client client; // Variable pour stocker les informations du client

  // Demande du nom du fichier du client à modifier
  printf("Nom du fichier du client à modifier : ");
  scanf("%s", client_filename);
  vider_buffer();

  // Ouverture du fichier en mode lecture
  fichier_client = fopen(client_filename, "r");

  // Vérification si l'ouverture du fichier a réussi
  if (fichier_client == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier du client.\n");
    return;
  }

  // Lecture des informations du client à partir du fichier
  fscanf(fichier_client, "Nom: %s\nPrénom: %s\nID: %d\nDate de naissance: %s\n",
         client.client_name, client.client_firstname, &client.client_id, client.date_of_birth);

  // Affichage des informations actuelles du client
  printf("Informations actuelles du client :\n");
  printf("Nom : %s\n", client.client_name);
  printf("Prénom : %s\n", client.client_firstname);
  printf("ID : %d\n", client.client_id);
  printf("Date de naissance : %s\n", client.date_of_birth);

  // Saisie des nouvelles informations pour le client
  printf("Nouveau nom du client : ");
  scanf("%s", client.client_name);
  vider_buffer();
  printf("Nouveau prénom du client : ");
  scanf("%s", client.client_firstname);
  vider_buffer();
  printf("Nouvel ID du client : ");
  scanf("%d", &client.client_id);
  vider_buffer();
  printf("Nouvelle date de naissance (JJ/MM/AAAA) : ");
  scanf("%s", client.date_of_birth);
  vider_buffer();

  // Fermeture du fichier
  fclose(fichier_client);

  // Génération du nouveau nom de fichier avec les nouvelles informations
  snprintf(new_client_filename, sizeof(new_client_filename), "%s_%s.txt",
           client.client_name, client.client_firstname);

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
  fprintf(fichier_client, "Nom: %s\nPrénom: %s\nID: %d\nDate de naissance: %s\n",
          client.client_name, client.client_firstname, client.client_id, client.date_of_birth);

  // Fermeture du fichier
  fclose(fichier_client);

  printf("Le client a été modifié avec succès.\n");
}


/////////////////////////////////////////////////
////////////////////////////////////////////////

// Fonction qui supprime les clients

void delete_client() {
  char client_name[MAX_NAME];
  FILE *fichier_clients;

  // Demande du nom du client à supprimer
  printf("Nom du client à supprimer : ");
  scanf("%s", client_name);
  vider_buffer();

  // Création du nom de fichier unique pour le client
  char filename[MAX_NAME + MAX_NAME +
                5]; // Nom du fichier = nom + prénom + ".txt"
  snprintf(filename, sizeof(filename), "%s.txt", client_name);

  // Vérification si le fichier existe
  if (access(filename, F_OK) == -1) {
    printf("Erreur : le fichier du client n'existe pas.\n");
    return;
  }

  // Affichage du nom du fichier à supprimer
  printf("Le fichier du client à supprimer est : %s\n", filename);

  // Demande de confirmation de suppression
  printf("Êtes-vous sûr de vouloir supprimer ce fichier ? (O/N) : ");
  char confirmation;
  scanf(" %c", &confirmation);
  vider_buffer();

  if (confirmation == 'O' || confirmation == 'o') {
    // Suppression du fichier
    if (remove(filename) != 0) {
      printf("Erreur : impossible de supprimer le fichier du client.\n");
      return;
    }

    printf("Le fichier du client a été supprimé avec succès.\n");
  } else {
    printf("La suppression du fichier du client a été annulée.\n");
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Fonction qui affiche un clients

void display_client() {
  FILE *fichier_clients;
  char client_name[MAX_NAME];
  char filename[MAX_NAME + MAX_NAME + 5];
  char line[MAX_NAME + MAX_NAME + MAX_HISTO +
            15]; // Variable temporaire pour lire une ligne du fichier

  // Demande du nom du client à afficher
  printf("Nom du client à afficher : ");
  scanf("%s", client_name);
  vider_buffer();

  // Création du nom de fichier unique pour le client
  snprintf(filename, sizeof(filename), "%s.txt", client_name);

  // Ouverture du fichier en mode lecture
  fichier_clients = fopen(filename, "r");

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
// Fonction chercher clients ( a revoir si ca marche)

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

#include "CLIENTS.H"

Client load_client(int client_id) {
    FILE* fichier_clients = fopen("clients.txt", "r");
    if (fichier_clients == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier des clients.\n");
        Client empty_client; // Client vide en cas d'erreur
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
        Client empty_client; // Client vide en cas de non correspondance
        empty_client.client_id = -1; // Valeur d'identifiant invalide
        return empty_client;
    }

    return client;
}
