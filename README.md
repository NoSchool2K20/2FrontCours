# NoSchool 2K20 - Partie Front

## Sommaire
1. [Accès au wiki de l'équipe](#wiki)
2. [Contexte global](#context)
3. [Le projet «Front-end cours»](#project)
4. [Installation du projet en local](#installation)
5. [Rappel des identifiants](#identifiants)

## <a id="wiki"></a>Accès au wiki "synthèse" de l'équipe
[Le wiki est accessible par ici](https://github.com/NoSchool2K20/2FrontCours/wiki)


## <a id="context"></a>Contexte global
La société Not Only a School - _NoSchool_ - est une société nouvellement créée et qui souhaite se positionner comme une plateforme de formation qualifiante en informatique à distance. <br/>
Elle souhaite lancer son MVP en juin 2020, sur le périmètre deux premiers parcours « analyste cyberdéfense »
et « développeur fullstack ». <br/>
Pour le lancement de son MVP, l’école propose une offre très simple : 19,99€/mois d’utilisation. C’est à dire que les early adopters seront facturés s’ils ont consulté au moins module de formation dans le mois. Il est prévu de limiter cette offre aux 1000 premiers inscrits qui serviront de base pour la conception du services jusqu’à ce que les autorisations administratives soient obtenues pour les prochaines étapes.<br/>
Rapidement l’école souhaite ouvrir une offre de niveau Master, qui vise en premier lieux un public de type « formation continue ». L’originalité pédagogique vient de la modularité des enseignements : chaque module peut être réalisé indépendamment et donne lieu à une certification ; des parcours regroupent des modules et donnent lieux à un diplôme. NoSchool souhaite attirer les personnes intéressées par un diplôme en format « cours du soir », autant que des personne recherchant une formation professionnelle, boostée par la réforme récente du CPF. La société souhaite aussi se différencier des MOOC classique en créant des échanges entre les étudiants. Enfin elle souhaite mettre en place du mentoring et des Hackathon ou Code JAM régulièrement, pour stimuler les étudiants. Ces derniers sujets sont toujours en cours d’études et ne font pas parti du MVP, pour lequel des fonds suffisants à sa réalisation et un an d’exploitation sont déjà mobilisés.

## <a id="project"></a> Le projet «Front-end cours»
Ce projet a été confié à la société MIAGE Studio, une agence web experte dans les technologies web. L’équipe projet se compose d’un chef de projet, d’un intégrateur et d’un développeurs front-end.

### Description
Cette application est une application web responsive.

### Stories
- **Story 1** : En tant que _«nouveau»_, je peux m’enregistrer, dans le but de créer mon compte
- **Story 2** : En tant que _«nouveau»_, si je dispose d’un compte, je peux me connecter, dans le but d’accéder à mes service étudiant ou professeur
- **Story 3** : En tant que _«nouveau»_, je peux demander une élévation de privilège afin de devenir _«étudiant»_ ou _«professeur»_
- **Story 4** : En tant que _«administrateur»_, je accepter ou refuser une élévation de privilège.
- **Story 5** : En tant que _«professeur»_, je peux créer un cours au sein d’un module.
- **Story 6** : En tant que _«étudiant»_, je peux consulter une liste de parcours et modules, dans le but de pouvoir sélectionner un cours
- **Story 7** : En tant que _«étudiant»_, je peux consulter un cours, afin de me former
- **Story 8** : En tant que _«étudiant»_, je peux échanger en direct avec les personnes qui suivent le même cours
- **Story 9** : En tant que _«étudiant»_, je peux consulter l’historique des communication de mon cours

### Règles de gestion
- **RG1** : lors d’une demande d’élévation de privilège, il est nécessaire de disposer de l’email du profil «nouveau»

### Technologies retenues
#### Démarche
L’application consiste principalement en une application web statique de type « Single Page Application », hébergée sur Clever Cloud.

#### Framework de développement
L’application doit être développée en ReasonReact, utiliser le gestionnaire de dépendance npm et être packagée avec webpack.<br/>
Le code produit devra être réaliséen ReasonML, via la libraire ReasonReact, compilée en JS avec Buckelscript.

#### Base d’authentification
Le fournisseur d’authentification unique est le service Auth & Indentity », la connexion est authentifiée par un token JWT signé et avec expiration

### Composant forum
Le composant de forum est réalisé par le projet « service forum », les modalités d’intégration sont un entrant que devra vous fournir l’équipe en charge de ce projet.

### Interface
Les contrats et la technologie des interfaces est un entrant que devra vous fournir l’équipe projet «back-end»

## <a id="installation"></a>Installation du projet en local
### Environnement requis
L'application est utilisable sur un système à noyaux UNIX (Linux/Mac) ou sur un Windows disposant de WSL. L'installation de node et de ses dépendances (npm notamment) est un impératif. Pour asssurer un fonctionnement complet du programme, nous requiérons l'utilisation de Node.js version 13.

### Commande à éxécuter pour le déploiement en local
Il faut d'abord cloner le dépôt:
  - Soit par HTTPS
```bash
git clone https://github.com/NoSchool2K20/2FrontCours.git
```
  - Soit par SSH
```bash
git clone git@github.com:NoSchool2K20/2FrontCours.git
```

Ensuite, dans le répertoire git cloné, jouer la commande
```bash
npm install
```
pour installer les dépendances du projet

<br/>Enfin, jouer la commande
```bash
npm run build
```
Pour construire une architecture fonctionnelle du projet.

### Lancement en mode serveur
```bash
npm run server
```
Le serveur est à ce moment là en écoute sur le port 8000
### Lancement en mode développement
```bash
npm run dev
```
Le serveur est alors en écoute sur le port 8000

## Rappel des identifiants
Les identifiants de service nous ont été fournis par l'équipe quatre pour faire des tests selon les rôles attribués.
### Compte nouveau :
```
id : nouveau@test.com
password : nouveau
```

### Compte etudiant :
```
id : etudiant@test.com
password : etudiant
```

### Compte prof :
```
id : professeur@test.com
password : professeur
```

### Compte admin :
```
email : admin@test.com
id : admin
password : admin
```
