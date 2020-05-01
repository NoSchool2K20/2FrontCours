describe('Création de compte / Connection', function() {
    it('Creation du compte', function() {
      cy.visit('http://localhost:8000/connection')
      cy.get('.create').click()
      cy.get('.createMail > input').click().type('lea@lea.fr')
      cy.get('.createMdp > input').click().type('testmdp')
      cy.get('.createPseudo > input').click().type('Lea')
      cy.get('.createName > input').click().type('V')
      cy.get('.createSurname > input').click().type('Lea')
      cy.get('.submitCreate > input[type="submit"]').click()
      cy.get('.FormulaireConnection').should('exists')
    })
    it('Connection avec le compte créé', function() {
      cy.get('input[name="email"]').click().type('lea@lea.fr')
      cy.get('input[name="password]').click().type('testmdp')
      cy.get('.login > input[type="submit"]').click()
      cy.location('pathname').should('eq', '/')
    })
  })

  describe('Présence des éléments de la page principale', function() {
    it('Parcours', function() {
      cy.visit('http://localhost:8000/')
      cy.get('.parcours').should('exists')
    })
    it('Modules', function() {
      cy.get('.menuModules').should('exists')
    })
    it('Cours', function() {
      cy.get('.cours').should('exists')
    })
  })

  describe('Ajout d\' un cours', function() {
    it('Validation du formulaire et redirection', function() {
      cy.visit('http://localhost:8000')
      cy.get('.buttonAjoutCours > button').click()
      cy.location('pathname').should('eq', '/addCours')
      cy.get('input[name="title"]').click().type('Base de données')
      cy.get('input[name="description"]').click().type('Un cours sur les bases de données')
      cy.get('input[name="video"]').click().type('https://www.youtube.com/embed/Ecv0PEOvLq0')
      cy.get('input[name="modules"]').click().type('Master 1 MIAGE')
      cy.get('.ajoutCours > input').click()
      cy.location('pathname').should('eq', '/')
    })
    it('Affichage du nouveau cours', function() {
      cy.get('.leCours > .titre').should('contain', 'Base de données')
    })
  })

  describe('Consultation d\'un cours', function() {
    it('Redirection', function() {
      cy.visit('http://localhost:8000')
      brands.get('.leCours > .titre').contains('POO').click()
      cy.location('pathname').should('eq', '/cours/POO')
    })
    it('Présence des éléments', function() {
      cy.get('.titreCours').should('exists')
      cy.get('.descriptionCours').should('exists')
      cy.get('.videoCours').should('exists')
    })
    it('Retour à l\'accueil', function() {
      cy.get('.accueilButton > button').click()
      cy.location('pathname').should('eq', '/')
    })
  })

  describe('Affichage des modules lors d\'un clic sur un parcours', function() {
    it('Redirection', function() {
      cy.visit('http://localhost:8000')
      brands.get('.parcours').contains('MIAGE').click()
      brands.get('.menuModules > button').should('contain', 'Licence 3  MIAGE')
      brands.get('.menuModules > button').should('contain', 'Master 1 MIAGE')
      brands.get('.menuModules > button').should('contain', 'Master 2 MIAGE')
    })
  })
  
  describe('Affichage des cours lors d\'un clic sur un module', function() {
    it('Redirection', function() {
      cy.visit('http://localhost:8000')
      brands.get('.menuModules > button').contains('Master 2 MIAGE').click()
      brands.get('.leCours > .titre').should('contain', 'QSI')
    })
  })