#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Projet de Julian Wicke et Ilyas R'kiouak

/*TO DO list:
 - Pouvoir créer un graph en entrant des valeurs
 - Utilisateur peut rentrer des valeurs pour qu'il puisse créer son graph
 - Pouvoir choisir un graph et le colorier
*/

// Définition des constantes
#define MAXN 100
#define WHITE 0
#define BLUE 1
#define RED 2
// #define n 100 // Taille solution

// Chaque sommet à un nom et un nombre de liens
typedef struct Sommet
{
  char nom[100];
  int nbLiens;
} Sommet;

int n, m;
int color[MAXN];
int matrice_adjacent[MAXN][MAXN];

// Fonction de création de fichier
int creationFichier()
{
  char nom_fichier[100];
  int nb_sommet;
  int nb_liaison;
  int depart_liaison;
  int arrivee_liaison;

  // Nom du fichier
  printf("Entrez le nom du fichier : ");
  scanf("%s", nom_fichier);
  strcat(nom_fichier, ".col");

  // Création du fichier
  FILE *fp;
  fp = fopen(nom_fichier, "w");

  // Si erreur
  if (fp == NULL)
  {
    printf("\n Impossible d'ouvrir le fichier\n");
    return 1;
  }

  // Ce qu'on demande
  printf("Combien de sommet voulez-vous ? : ");
  scanf("%d", &nb_sommet);

  printf("Combien de liaison avez-vous ? : ");
  scanf("%d", &nb_liaison);

  // Ce qu'on écrit dedans
  fprintf(fp, "c Nom du fichier : %s \n \n", &nom_fichier);
  fprintf(fp, "p edge %d %d \n", nb_sommet, nb_liaison);

  // Liaison
  for (int i = 0; i < nb_liaison; i++)
  {
    printf("Ou demarre la liaison ? : ");
    scanf("%d", &depart_liaison);
    printf("Ou finit la liaison ? : ");
    scanf("%d", &arrivee_liaison);
    fprintf(fp, "e %d %d \n", depart_liaison, arrivee_liaison);
    if (i != nb_liaison - 1)
    {
      printf("Veuillez entrer une nouvelle liaison \n");
    }
  }
  // Fermeture
  fclose(fp);
}

// Fonction de lecture de fichier
int lectureFichier()
{
  char str[100];
  char nomFichierOuvert[100];
  char sommetFichier[5];
  char liaisonFichier[5];
  int compteurMot = 0;
  char ligne[100];

  FILE *fichierOuvert;

  printf("Entrez le nom du fichier : ");
  scanf("%s", nomFichierOuvert);

  fichierOuvert = fopen(nomFichierOuvert, "r");

  // Si erreur
  if (fichierOuvert == NULL)
  {
    printf("Le fichier %s n'existe pas \n", nomFichierOuvert);
    return 1;
  }

  // Lire chaque ligne jusqu'à ce qu'une ligne commençant par "p" soit trouvée
  while (fgets(str, sizeof(str), fichierOuvert) != NULL)
  {
    if (str[0] == 'p')
    {
      // La ligne a été trouvée, sortir de la boucle
      break;
    }
  }

  // Récupérer chaque mot de la ligne
  char *token = strtok(str, " ");
  while (token != NULL)
  {
    compteurMot++;
    if (compteurMot == 3)
    {
      // Le troisième mot a été trouvé, c'est le nombre de sommet
      strcpy(sommetFichier, token);
    }
    if (compteurMot == 4)
    {
      // Le quatrième mot a été trouvé, c'est le nombre de liaison
      strcpy(liaisonFichier, token);
      break;
    }
    token = strtok(NULL, " ");
  }

  printf("Le nombre de sommet est de : %s \n", sommetFichier);

  printf("Le nombre de liaison est de : %s \n", liaisonFichier);

  // strtok = prend comme arguments une chaîne de caractères (la ligne à découper) et un caractère de séparation (ici, un espace) retourne un pointeur vers la première chaîne de caractères découpée
  // strstr = prend comme arguments une chaîne de caractères (la ligne à analyser) et une sous-chaîne de caractères (le chiffre à rechercher) retourne un pointeur vers la première occurrence de la sous-chaîne de caractères dans la chaîne de caractères

  /////////////////////////////////////////
  // Création du tableau de sommets
  /////////////////////////////////////////

  // Convertir sommetFichier et liaisonFichier en int
  int sommetInt = atoi(sommetFichier);
  int liaisonInt = atoi(liaisonFichier);

  struct Sommet tableau[sommetInt];

  // Remplir le tableau
  for (int i = 0; i < sommetInt; i++)
  {
    // Le nom du sommet est un chiffre
    sprintf(tableau[i].nom, "%d", i + 1);
    tableau[i].nbLiens = 0;
  }

  // Lire chaque ligne jusqu'à ce qu'une ligne commençant par "e" soit trouvée
  while (fgets(ligne, sizeof(ligne), fichierOuvert) != NULL)
  {
    // Si la ligne commence par "e"
    if (ligne[0] == 'e')
    {
      // Si sur la ligne il y a un chiffre alors on ajoute +1 au nombre de liens du sommet
      for (int i = 0; i < sommetInt; i++)
      {
        if (strstr(ligne, tableau[i].nom) != NULL)
        {
          tableau[i].nbLiens++;
        }
      }
    }
  }

  int afficherSommets;
  // Demander si il veut affichet les sommets
  printf("Voulez-vous afficher les sommets de ce fichier ? (1 = oui, 0 = non) : ");
  scanf("%d", &afficherSommets);

  if (afficherSommets == 1)
  {
    // Afficher le tableau
    printf("Voici les sommets et leurs liaisons: \n");
    for (int i = 0; i < sommetInt; i++)
    {
      printf("Le sommet %s possede %d liaisons \n", tableau[i].nom, tableau[i].nbLiens);
    }
    printf("\n");
  }
  else
  {
    printf("Vous avez choisi de ne pas lire les sommets du fichier %s \n\n", nomFichierOuvert);
  }

  // // Demander si on veut toutes les liaisons du fichier
  // int choixLectureToutesLiaisons;
  // printf("Voulez-vous afficher toutes les liaisons du fichier ? (oui = 1 / non = 0) : ");
  // scanf("%d", &choixLectureToutesLiaisons);
  // if (choixLectureToutesLiaisons == 1)
  // {
  //   printf("Les liaisons du fichier : \n");
  //   // Lire chaque ligne jusqu'à ce qu'une ligne commençant par "e" soit trouvée
  //   while (fgets(ligne, sizeof(ligne), fichierOuvert) != NULL)
  //   {
  //     // Si la ligne commence par "e"
  //     if (ligne[0] == 'e')
  //     {
  //       printf("%s", ligne);
  //     }
  //   }
  //   printf("\n");
  // }

  // // Fermer le fichier
  // fclose(fichierOuvert);
}

// Fonction pour modifier un fichier
int modifierFichier()
{
  printf("en cours de developpement \n");
  // char str[100];
  // char nomFichierOuvert[100];

  // FILE *fichierOuvert;

  // printf("Entrez le nom du fichier : ");
  // scanf("%s", nomFichierOuvert);

  // fichierOuvert = fopen(nomFichierOuvert, "r");

  // // Si erreur
  // if (fichierOuvert == NULL)
  // {
  //   printf("Le fichier %s n'existe pas \n", nomFichierOuvert);
  //   return 1;
  // }

  // // Que voulez-vous modifier ?
  // int choixModif;
  // printf("Que voulez-vous modifier ? (0 = rien modifier, 1 = sommet, 2 = une liaison) : ");
  // scanf("%d", &choixModif);

  // // Si on veut modifier le fichier
  // if (choixModif == 1)
  // {
  //   char newSommetFichier[100];
  //   char newLiaisonFichier[100];
  //   char sommetFichier[100];
  //   char liaisonFichier[100];

  //   // Affiche le nombre de sommets et de liaisons et demande à l'utilisateur de choisir une nouvelle valeur
  //   // printf("Le nombre de sommets est de %s et le nombre de liaisons est de %s \n", sommetFichier, liaisonFichier);
  //   printf("Entrez le nouveau nombre de sommets : ");
  //   scanf("%s", newSommetFichier);
  //   printf("Entrez le nouveau nombre de liaisons : ");
  //   scanf("%s", newLiaisonFichier);

  //   int compteurMot = 0;
  //   // Remplacer le nombre de sommets et de liaisons dans le fichier
  //   while (fgets(str, 100, fichierOuvert) != NULL)
  //   {
  //     // if (strstr(str, "p edge") != NULL)
  //     // {
  //     //   // Remplacer le nombre de sommets
  //     //   char *pos = strstr(str, sommetFichier);
  //     //   if (pos != NULL)
  //     //   {
  //     //     pos[0] = ' ';
  //     //   }
  //     //   // Remplacer le nombre de liaisons
  //     //   char *pos2 = strstr(str, liaisonFichier);
  //     //   if (pos2 != NULL)
  //     //   {
  //     //     pos2[0] = ' ';
  //     //   }
  //     // }
  //     if (str[0] == 'p')
  //     {
  //       // récupérer le 3e mot de la ligne et le remplacer par le nouveau nombre de sommets
  //       char *token = strtok(str, " ");
  //       while (token != NULL)
  //       {
  //         compteurMot++;
  //         if (compteurMot == 3)
  //         {
  //           token = newSommetFichier;
  //         }
  //         if (compteurMot == 4)
  //         {
  //           token = newLiaisonFichier;
  //         }
  //         token = strtok(NULL, " ");
  //       }

  //       printf("Le nombre de sommet est de : %s \n", newSommetFichier);

  //       printf("Le nombre de liaison est de : %s \n", newLiaisonFichier);
  //     }
  //   }
  // }
}

int recupSommetEtLiaison(char nomFichierOuvert[100])
{

  char str[100];
  char sommet[5];
  char liaison[5];
  int compteurMot = 0;

  FILE *fichierOuvert;

  fichierOuvert = fopen(nomFichierOuvert, "r");

  // Si erreur
  if (fichierOuvert == NULL)
  {
    printf("Le fichier %s n'existe pas\n", nomFichierOuvert);
    return 1;
  }

  // Lire chaque ligne jusqu'à ce qu'une ligne commençant par "p" soit trouvée
  while (fgets(str, sizeof(str), fichierOuvert) != NULL)
  {
    if (str[0] == 'p')
    {
      // La ligne a été trouvée, sortir de la boucle
      break;
    }
  }

  // Récupérer chaque mot de la ligne
  char *token = strtok(str, " ");

  while (token != NULL)
  {
    compteurMot++;

    if (compteurMot == 3)
    {
      // Le quatrième mot a été trouvé, c'est le nombre de sommet
      strcpy(sommet, token);
    }

    if (compteurMot == 4)
    {
      // Le quatrième mot a été trouvé, c'est le nombre de liaison
      strcpy(liaison, token);
      break;
    }

    token = strtok(NULL, " ");
  }

  n = atoi(sommet);
  m = atoi(liaison);

  return 0;
}

// fonctions Welsh-Powell
void parcours_visit(int u)
{ // u est le sommet à visiter
  color[u] = BLUE;
  for (int v = 0; v < n; v++)
  { // v est le sommet voisin de u
    if (matrice_adjacent[u][v] && color[v] == WHITE)
    { // Si il y a une liaison entre u et v et que v n'a pas encore été visité
      parcours_visit(v);
    }
  }
  color[u] = RED;
}

// Parcours en profondeur
void parcoursEnProfondeur()
{
  for (int u = 0; u < n; u++)
  {
    color[u] = WHITE;
  }

  for (int u = 0; u < n; u++)
  {
    if (color[u] == WHITE)
    {
      parcours_visit(u);
    }
  }
}

void colorationGraph()
{
  int degreMax = 0;
  int degres[MAXN];

  parcoursEnProfondeur();

  // Trouve le degré maximum (mise à jour de degreMax)
  for (int u = 0; u < n; u++)
  {
    int degre = 0;
    for (int v = 0; v < n; v++)
    {
      degre += matrice_adjacent[u][v];
    }
    degres[u] = degre;
    if (degre > degreMax)
    {
      degreMax = degre;
    }
  }

  // Trie les sommets par degré décroissant
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (degres[i] < degres[j])
      {
        int temp = degres[i];
        degres[i] = degres[j];
        degres[j] = temp;

        temp = color[i];
        color[i] = color[j];
        color[j] = temp;
      }
    }
  }

  // Attribue une couleur à chaque sommet
  for (int u = 0; u < n; u++)
  {
    int couleur_minimum[MAXN];

    // initialise couleur_minimum
    for (int i = 0; i < degreMax + 1; i++)
    {
      couleur_minimum[i] = 0;
    }

    // verification des sommets adjacents
    for (int v = 0; v < n; v++)
    {
      if (matrice_adjacent[u][v])
      {
        couleur_minimum[color[v]] = 1;
      }
    }

    // choisie l'index de la couleur
    int c;
    for (c = 0; c < degreMax + 1; c++)
    {
      if (couleur_minimum[c] == 0)
      {
        break;
      }
    }

    // attribution des couleurs
    color[u] = c;
  }
}

// void hill_climbing(int solution[], int nb_iterations_max, int solution_finale[])
// {
//   // Initialisez la solution finale avec la solution initiale
//   for (int i = 0; i < n; i++)
//   {
//     solution_finale[i] = solution[i];
//   }

//   // Répétez l'algorithme de Hill-Climbing jusqu'à ce que le nombre maximum d'itérations soit atteint
//   for (int i = 0; i < nb_iterations_max; i++)
//   {
//     // Calculez la solution voisine
//     int solution_voisine[n];
//     voisin(solution_finale, solution_voisine);

//     // Si la solution voisine est meilleure que la solution finale, mettez à jour la solution finale
//     if (cout(solution_voisine) < cout(solution_finale))
//     {
//       for (int j = 0; j < n; j++)
//       {
//         solution_finale[j] = solution_voisine[j];
//       }
//     }
//   }
// }

// int cout(int couleurs[], int nb_sommets, int **matrice_adjacent)
// {
//   int nb_conflits = 0;
//   // Parcourez tous les sommets du graphe
//   for (int u = 0; u < nb_sommets; u++)
//   {
//     // Parcourez tous les sommets voisins de u
//     for (int v = 0; v < nb_sommets; v++)
//     {
//       if (matrice_adjacent[u][v] && couleurs[u] == couleurs[v])
//       {
//         // Si u et v sont voisins et ont la même couleur, incrémentez le nombre de conflits
//         nb_conflits++;
//       }
//     }
//   }
//   // Renvoyez le nombre de conflits divisé par 2, car chaque conflit est compté deux fois
//   return nb_conflits / 2;
// }

// void voisin(int couleurs[], int nb_sommets, int **matrice_adjacent, int couleurs_voisines[])
// {
//   // Copiez les couleurs courantes dans les couleurs voisines
//   for (int i = 0; i < nb_sommets; i++)
//   {
//     couleurs_voisines[i] = couleurs[i];
//   }

//   // Choisissez deux sommets au hasard
//   int u = rand() % nb_sommets;
//   int v = rand() % nb_sommets;
//   // Échangez leurs couleurs
//   int temp = couleurs_voisines[u];
//   couleurs_voisines[u] = couleurs_voisines[v];
//   couleurs_voisines[v] = temp;
// }

int main(void)
{
  int choixCreer;
  int choixLire;
  int choixModif;
  int choixColorier;
  int choixColorierHill;
  int choixAfficheColo;
  char fichier[100];
  char AfficherColo[100];

  // Demender si il veut créer un fichier
  printf("Voulez-vous creer un fichier ? (1 = oui, 0 = non) : ");
  scanf("%d", &choixCreer);

  if (choixCreer == 1)
  {
    creationFichier();
  }
  else
  {
    printf("Vous avez choisi de ne pas creer de fichier \n\n");
  }

  // Demander si il veut lire un fichier
  printf("Voulez-vous lire un fichier ? (1 = oui, 0 = non) : ");
  scanf("%d", &choixLire);

  if (choixLire == 1)
  {
    lectureFichier();
  }
  else
  {
    printf("Vous avez choisi de ne pas lire de fichier \n\n");
  }

  // Colorier un graphique
  printf("Voulez-vous colorer un graphique avec Welsh-Powell ? (1 = oui, 0 = non) : ");
  scanf("%d", &choixColorier);

  if (choixColorier == 1)
  {
    ///////////Dupliquer////////////

    char fichierOrigine[100];
    char fichierColo[100];

    // Demander le nom du fichier
    printf("Entrez le nom du fichier : ");
    scanf("%s", fichierOrigine);

    // Ouvrir le fichier source en lecture
    FILE *fichierSource = fopen(fichierOrigine, "r");
    if (fichierSource == NULL)
    {
      // Erreur d'ouverture du fichier
      perror("Erreur d'ouverture du fichier source");
      exit(EXIT_FAILURE);
    }

    // Demander le nom du fichier
    printf("Entrez le nouveau nom du fichier ou il y aura la coloration : ");
    scanf("%s", fichierColo);
    strcat(fichierColo, ".col");

    // Ouvrir le fichier cible en écriture
    FILE *fichierCible = fopen(fichierColo, "w");
    if (fichierCible == NULL)
    {
      // Erreur d'ouverture du fichier
      perror("Erreur d'ouverture du fichier cible");
      exit(EXIT_FAILURE);
    }

    // Lire chaque ligne du fichier source et l'écrire dans le fichier cible
    char ligneV2[1024];
    while (fgets(ligneV2, sizeof(ligneV2), fichierSource) != NULL)
    {
      fputs(ligneV2, fichierCible);
      // écrire le nouveau nom fichier à la première ligne
      if (ligneV2[0] == 'c')
      {
        fprintf(fichierCible, "c Nouveau nom du fichier : %s", fichierColo);
      }
    }

    // Fermer les fichiers source et cible
    if (fclose(fichierSource) != 0)
    {
      perror("Erreur de fermeture du fichier source");
      exit(EXIT_FAILURE);
    }

    if (fclose(fichierCible) != 0)
    {
      perror("Erreur de fermeture du fichier cible");
      exit(EXIT_FAILURE);
    }

    /////////////////////////

    recupSommetEtLiaison(fichierColo);

    FILE *fichierOuvert = fopen(fichierColo, "r");

    if (fichierOuvert == NULL)
    {
      printf("Le fichier %s n'existe pas\n", fichierColo);
      return 0;
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichierOuvert) != NULL)
    {

      if (ligne[0] == 'e')
      {
        char sommet1[5], sommet2[5];
        int compteurMot = 0;
        int u, v;

        // Récupérer chaque mot de la ligne
        char *token = strtok(ligne, " ");

        while (token != NULL)
        {
          compteurMot++;

          if (compteurMot == 2)
          {
            strcpy(sommet1, token);
          }

          if (compteurMot == 3)
          {
            strcpy(sommet2, token);
            break;
          }

          token = strtok(NULL, " ");
        }

        u = atoi(sommet1);
        v = atoi(sommet2);

        matrice_adjacent[u][v] = 1;
        matrice_adjacent[v][u] = 1;
      }
    }

    colorationGraph();

    fichierOuvert = fopen(fichierColo, "a");
    for (int u = 0; u < n; u++)
    {
      fprintf(fichierOuvert, "s %d %d\n", u + 1, color[u]);
      printf("Sommet %d : couleur %d\n", u + 1, color[u]);
    }
    printf("\n");
  }
  else
  {
    printf("Vous avez choisi de ne pas colorer le graphique avec Welsh-Powell\n\n");
  }

  // Colorier un graphique
  printf("Voulez-vous colorer un graphique avec Hill-Climbing ? (1 = oui, 0 = non) : ");
  scanf("%d", &choixColorierHill);
  if (choixColorierHill == 1)
  {
    printf("L'algorithme Hill-Climbing n'est pas encore disponible\n\n");

    // // Initialisez la solution courante avec une coloration aléatoire
    // int couleurs[nb_sommets];
    // for (int i = 0; i < nb_sommets; i++)
    // {
    //   couleurs[i] = rand() % nb_couleurs;
    // }

    // // Répétez jusqu'à ce qu'une solution optimale soit trouvée ou qu'un nombre maximal d'itérations soit atteint
    // int max_iterations = 1000;
    // for (int i = 0; i < max_iterations; i++)
    // {
    //   // Calculez la solution voisine
    //   int couleurs_voisines[nb_sommets];
    //   voisin(couleurs, nb_sommets, matrice_adjacent, couleurs_voisines);

    //   // Calculez le nombre de conflits de couleur dans la solution courante et la solution voisine
    //   int cout_courant = cout(couleurs, nb_sommets, matrice_adjacent);
    //   int cout_voisin = cout(couleurs_voisines, nb_sommets, matrice_adjacent);

    //   // Si la solution voisine a moins de conflits, utilisez-la comme nouvelle solution courante
    //   if (cout_voisin < cout_courant)
    //   {
    //     for (int i = 0; i < nb_sommets; i++)
    //     {
    //       couleurs[i] = couleurs_voisines[i];
    //     }
    //   }

    //   // Si aucun conflit n'est présent, arrêtez l'algorithme
    //   if (cout_courant == 0)
    //   {
    //     break;
    //   }
    // }

    // // Affichez ou enregistrez la solution finale
    // for (int i = 0; i < nb_sommets; i++)
    // {
    //   printf("Le sommet %d est de couleur %d\n", i, couleurs[i]);
    // }
  }
  else
  {
    printf("Vous avez choisi de ne pas colorer le graphique avec Hill-Climbing\n\n");
  }

  // Afficher la coloration d'un graphique

  printf("Voulez-vous afficher la coloration d'un graphique ? (1 = oui, 0 = non) : ");
  scanf("%d", &choixAfficheColo);

  if (choixAfficheColo == 1)
  {
    printf("Entrez le nom du fichier : ");
    scanf("%s", AfficherColo);

    FILE *fichierAfficheColo = fopen(AfficherColo, "r");

    // Vérifier si le fichier existe
    if (fichierAfficheColo == NULL)
    {
      printf("Le fichier %s n'existe pas\n", AfficherColo);
      return 0;
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichierAfficheColo) != NULL)
    {
      if (ligne[0] == 's')
      {
        char sommet[5], couleur[5];
        int compteurMot = 0;

        // Récupérer chaque mot de la ligne
        char *token = strtok(ligne, " ");

        while (token != NULL)
        {
          compteurMot++;

          if (compteurMot == 2)
          {
            strcpy(sommet, token);
          }

          if (compteurMot == 3)
          {
            strcpy(couleur, token);
            break;
          }

          token = strtok(NULL, " ");
        }

        printf("Le sommet %s est de couleur %s", sommet, couleur);
      }
    }
  }
  else
  {
    printf("Vous avez choisi de ne pas afficher la coloration d'un graphique");
  }

  // Demander si il veut modifier un fichier
  // printf("Voulez-vous modifier un fichier ? (1 = oui, 0 = non) : ");
  // scanf("%d", &choixModif);

  // if (choixModif == 1)
  // {
  //   modifierFichier();
  // }
  // else
  // {
  //   printf("Vous avez choisi de ne pas modifier un fichier \n\n");
  // }

  return 0;
}
