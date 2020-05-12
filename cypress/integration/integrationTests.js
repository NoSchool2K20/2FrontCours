before(() => {
  cy.clearLocalStorageSnapshot();
});

beforeEach(() => {
  cy.restoreLocalStorage();
});

afterEach(() => {
  cy.saveLocalStorage();
});

describe('Création de compte / Connection', function() {
    it('Creation du compte', function() {
      cy.visit('http://localhost:8000/connection')
      cy.wait(500)
      cy.get('.create').click()
      cy.wait(500)
      cy.get('.createMail > input').click().type('test@prof.fr')
      cy.get('.createMdp > input').click().type('testmdp')
      cy.get('.createPseudo > input').click().type('Test')
      cy.get('.createName > input').click().type('Cypress')
      cy.get('.createSurname > input').click().type('Test')
      cy.get('.submitCreate > input[type="submit"]').click()
      cy.wait(500)
      cy.get('.FormulaireConnection').should('exist')
    })
    it('Connection avec le compte créé', function() {
      cy.visit('http://localhost:8000/connection')
      cy.wait(500)
      cy.get('input[name="email"]').click().type('test@prof.fr')
      cy.get('input[name="password"]').click().type('testmdp')
      cy.get('.login > input[type="submit"]').click()
      cy.location('pathname').should('eq', '/')
    })
  })

  describe('Pas de contenu avec le profil nouveau', function() {
  it('Affichage du message', function() {
    cy.wait(500)
    cy.get('.accueilNouveau').should('exist')
  })
  it('Demande d\'élévation de pivilèges', function() {
    cy.get('.buttonDroits').click()
    cy.get('.prof > input').click()
    cy.get('.submitElevation').click()
    cy.location('pathname').should('eq', '/')
  })
  })

  // TESTS PROFIL ETUDIANT
  describe('Connection profil nouveau', function() {
    it('Deconnexion puis reconnexion ', function() {
      cy.get('.deconnection').click()
      cy.wait(500)
      cy.get('input[name="email"]').click().type('etudiant@test.com')
      cy.get('input[name="password"]').click().type('etudiant')
      cy.get('.login > input[type="submit"]').click()
      cy.location('pathname').should('eq', '/')
    })
  })
  describe('Présence des éléments de la page principale', function() {
    it('Parcours', function() {
      cy.get('.parcours').should('exist')
    })
    it('Modules', function() {
      cy.get('.menuModules').should('exist')
    })
    it('Cours', function() {
      cy.get('.cours').should('exist')
    })
  })

  describe('Affichage des modules lors d\'un clic sur un parcours', function() {
    it('Tous les modules sont affichés', function() {
      cy.get('.parcours').contains('Developpeur Fullstack').click()
      cy.get('button[name="boutonModule"]').contains('Master 1 DF').should('exist')
      cy.get('button[name="boutonModule"]').contains('Master 2 DF').should('exist')
    })
  })
  
  describe('Affichage des cours lors d\'un clic sur un module', function() {
    it('Les cours correspondants sont affichés', function() {
      cy.get('.parcours').contains('Analyste Cyberdefense').click()
      cy.get('.menuModules > button').contains('Master 1 AC').click()
      cy.get('.leCours > .titre').contains('Rappels mathématiques').should('exist')
    })
  })

  describe('Consultation d\'un cours', function() {
    it('Redirection', function() {
      cy.wait(200)
      cy.get('.leCours > button').eq(0).click()
      cy.location('pathname').should('eq', '/cours/Rappels%20math%C3%A9matiques')
    })
    it('Présence des éléments de cours', function() {
      cy.get('.titreCours').should('exist')
      cy.get('.descriptionCours').should('exist')
      cy.get('.videoCours').should('exist')
    })
    it('Présence du forum', function() {
      cy.get('.forumButton > button').click({force: true})
      cy.get('.theForum').should('exist')
    })
    it('Retour à l\'accueil', function() {
      cy.get('.accueilButton > button').click({force: true})
      cy.location('pathname').should('eq', '/')
    })
  })

  // TESTS PROFIL PROFESSEUR

  describe('Connection profil professeur', function() {
    it('Deconnexion puis reconnexion ', function() {
      cy.get('.deconnection').click()
      cy.wait(500)
      cy.get('input[name="email"]').click().type('professeur@test.com')
      cy.get('input[name="password"]').click().type('professeur')
      cy.get('.login > input[type="submit"]').click()
      cy.location('pathname').should('eq', '/')
    })
  })
  describe('Ajout d\' un cours', function() {
    it('Validation du formulaire et redirection', function() {
      cy.wait(500)
      cy.get('.buttonAjoutCours > button').click()
      cy.location('pathname').should('eq', '/addCours')
      cy.get('input[name="title"]').click().type('Tests avec Cypress')
      cy.get('input[name="description"]').click().type('Ce cours vise à découvrir l\'outil Cypress.')
      cy.get('input[name="video"]').click().type('https://www.youtube.com/embed/fKG9KaOTnxw')
      cy.get('input[name="modules"]').click().type('Master 2 DF')
      cy.get('.ajoutCours > input').click()
      cy.location('pathname').should('eq', '/')
    })
    it('Affichage du nouveau cours', function() {
      cy.get('.parcours').contains('Developpeur Fullstack').click()
      cy.get('.menuModules > button').contains('Master 2 DF').click()
      cy.get('.leCours > .titre').should('contain', 'Tests avec Cypress')
    })
  })

  //TESTS PROFIL ADMIN

  describe('Connection profil administrateur', function() {
    it('Deconnexion puis reconnexion ', function() {
      cy.get('.deconnection').click()
      cy.wait(500)
      cy.get('input[name="email"]').click().type('admin@test.com')
      cy.get('input[name="password"]').click().type('admin')
      cy.get('.login > input[type="submit"]').click()
      cy.location('pathname').should('eq', '/')
    })
    it('Consultation des demandes d\'élévation', function() {
      cy.get('.consultElevations').click({force: true})
      cy.location('pathname').should('eq', '/acceptPrivileges')
      cy.get('.accepter').click()
    })
    it('Vérification du nouveau profil', function() {
      cy.wait(500)
      cy.get('.accueilButton > button').click({force: true})
      cy.get('.deconnection').click()
      cy.wait(500)
      cy.get('input[name="email"]').click().type('test@prof.fr')
      cy.get('input[name="password"]').click().type('testmdp')
      cy.get('.login > input[type="submit"]').click()

      cy.get('.buttonAjoutCours > button').should('exist')

    })
  })


  