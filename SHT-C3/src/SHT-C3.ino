#include <Adafruit_SHTC3.h> // Bibliothèque pour le capteur SHTC3
#include <Wire.h> // Bibliothèque pour la communication I2C
#include <SPI.h> // Obliger de mettre cette bibliothèque même si on est en I2C
//car la bibliotheque adafruit doit pouvoir trouver le SPI

// On crée un objet représentant le capteur
Adafruit_SHTC3 shtc3;

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600); // Ouvre le port série à 9600 bauds
  while (!Serial) delay(10); // Attendre que le moniteur série soit prêt (utile sur certains appareils)

  // Initialisation du capteur SHTC3
  if (!shtc3.begin()) { // Vérifie si le capteur est correctement détecté
    Serial.println("Erreur : Capteur SHTC3 non détecté !"); // Message d'erreur si le capteur n'est pas trouvé
    while (1) delay(10); // Stoppe le programme pour éviter d'aller plus loin
  }
  Serial.println("Capteur SHTC3 détecté avec succès !"); // Confirmation que le capteur est prêt
}

void loop() {
  // Création de deux variables pour stocker les données
  sensors_event_t humidity, temp; // `humidity` pour l'humidité, `temp` pour la température

  // Lecture des données depuis le capteur
  if (shtc3.getEvent(&humidity, &temp)) { // `getEvent` retourne true si les données sont bien lues
    // Affichage de la température
    Serial.print("Température : ");
    Serial.print(temp.temperature); // Affiche la valeur de la température
    Serial.println(" °C"); // Ajoute l'unité pour que ce soit plus clair

    // Affichage de l'humidité relative
    Serial.print("Humidité : ");
    Serial.print(humidity.relative_humidity); // Affiche la valeur de l'humidité
    Serial.println(" %"); // Ajoute l'unité pour l'humidité

    // Ligne séparatrice pour une meilleure lisibilité des données dans le moniteur série
    Serial.println("----------------------");
  } else {
    // Si la lecture des données échoue, on affiche un message d'erreur
    Serial.println("Erreur : Impossible de lire les données du capteur !");
  }

  delay(1000); // Attend 1 seconde avant de refaire une lecture pour éviter d'inonder le moniteur série
}

