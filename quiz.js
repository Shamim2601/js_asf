// Stub for the adminQuizList function
// Returns a list of all quizzes owned by the current user

function adminQuizList(authUserId) {
    return { 
        quizzes: [
            {
                quizId: 1,
                name: 'My Quiz',
            }
        ] 
    }
}

// Stub for the adminQuizCreate function
// Returns an object containing the new quizId

function adminQuizCreate(authUserId, name, description) {
    return {
        quizId: 2
      }
}

// Stub for the adminQuizRemove function
// Returns an empty object

function adminQuizRemove(authUserId, quizId) {
    return { 

    }
}

// Stub for the adminQuizInfo function
// Returns an object containing the quiz information

function adminQuizInfo(authUserId, quizId) {
    return {
        quizId: 1,
        name: 'My Quiz',
        timeCreated: 1683125870,
        timeLastEdited: 1683125871,
        description: 'This is my quiz',
      }
}

// Stub for the adminQuizNameUpdate function
// Returns an empty object

function adminQuizNameUpdate(authUserId, quizId, name) {
    return {

    }
}

// Stub for the adminQuizDescriptionUpdate function
// Returns an empty object

function adminQuizDescriptionUpdate(authUserId, quizId, description) {
    return {

    }
}


adminQuizNameUpdate("1", "fun");
adminQuizInfo("1");