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
    /*it('Creation du compte', function() {
      cy.visit('http://localhost:8000/connection')
      cy.wait(500)
      cy.get('.create').click()
      cy.wait(500)
      cy.get('.createMail > input').click().type('lea@lea.fr')
      cy.get('.createMdp > input').click().type('testmdp')
      cy.get('.createPseudo > input').click().type('Lea')
      cy.get('.createName > input').click().type('V')
      cy.get('.createSurname > input').click().type('Lea')
      cy.get('.submitCreate > input[type="submit"]').click()
      cy.wait(500)
      cy.get('.FormulaireConnection').should('exist')
    })*/
    it('Connection avec le compte créé', function() {
      
      cy.visit('http://localhost:8000/connection')
      cy.wait(500)
      cy.get('input[name="email"]').click().type('lea@lea.fr')
      cy.get('input[name="password"]').click().type('testmdp')
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
      cy.get('.parcours').contains('MIAGE').click()
      cy.get('button[name="boutonModule"]').contains('Licence 3 MIAGE').should('exist')
      cy.get('button[name="boutonModule"]').contains('Master 1 MIAGE').should('exist')
      cy.get('button[name="boutonModule"]').contains('Master 2 MIAGE').should('exist')
    })
  })
  
  describe('Affichage des cours lors d\'un clic sur un module', function() {
    it('Les cours correspondants sont affichés', function() {
      cy.get('.menuModules > button').contains('Master 2 MIAGE').click()
      cy.get('.leCours > .titre').should('contain', 'QSI')
    })
  })

  describe('Ajout d\' un cours', function() {
    /*it('Validation du formulaire et redirection', function() {
      cy.wait(500)
      cy.get('.buttonAjoutCours > button').click()
      cy.location('pathname').should('eq', '/addCours')
      cy.get('input[name="title"]').click().type('Base de données')
      cy.get('input[name="description"]').click().type('Un cours sur les bases de données')
      cy.get('input[name="video"]').click().type('https://www.youtube.com/embed/Ecv0PEOvLq0')
      cy.get('input[name="modules"]').click().type('Master 1 MIAGE')
      cy.get('.ajoutCours > input').click()
      cy.location('pathname').should('eq', '/')
    })*/
    it('Affichage du nouveau cours', function() {
      cy.get('.menuModules > button').contains('Master 1 MIAGE').click()
      cy.get('.leCours > .titre').should('contain', 'Base de données')
    })
  })

  describe('Consultation d\'un cours', function() {
    it('Redirection', function() {
      cy.get('.menuModules > button').contains('Licence 3 MIAGE').click()
      cy.wait(200)
      cy.get('.leCours > button').click()
      cy.location('pathname').should('eq', '/cours/POO')
    })
    it('Présence des éléments', function() {
      cy.get('.titreCours').should('exist')
      cy.get('.descriptionCours').should('exist')
      cy.get('.videoCours').should('exist')
    })
    it('Retour à l\'accueil', function() {
      cy.get('.accueilButton > button').click({force: true})
      cy.location('pathname').should('eq', '/')
    })
  })

  