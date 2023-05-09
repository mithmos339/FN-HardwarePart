var admin = require("firebase-admin");
// Initialize Firebase Admin SDK with service account credentials
var serviceAccount = require("./tactical-app-firebase-adminsdk-vfdhh-251439f642.json");



admin.initializeApp({
  credential: admin.credential.cert(serviceAccount),
  databaseURL: "https://tactical-app-default-rtdb.firebaseio.com"
});

// Get a reference to the Realtime Database
const database = admin.database();

// Get a reference to the Firestore
const firestore = admin.firestore();
// get account from flutter and save account to username
const username = 'username';
const ref = database.ref("/" + username);
ref.on("value", (snapshot) => {

  const data = snapshot.val();
  const score = () => {
    const result = data.plus - data.miss
    if (result >= 0) {
      return result
    } else {
      return 0
    };
  }
  console.log(data.plus1+ data.plus2)
  ref.update({plus : data.plus1 + data.plus2})
  const document = {
    Miss: data.miss,
    Plus: data.plus,
    Email: data.email,
    Time: data.time,
    Score: score()
  }
  const resetData = {
    end: 0,
    miss: 0,
    email: '',
    plus: 0,
    plus1: 0,
    plus2: 0,
    status: 0,
    time: 180,
  };
  // Convert the data to an array of objects
  // Save the data to Firestore
  if (data.end === 1) {
    document.Time = 180 - document.Time
    firestore.collection("TestData").add(document);
    ref.update(resetData)
  }
  
});
// todo from chat gpt : change name dynamic by user account
// Get a reference to the Realtime Database for the current user
// const database = admin.database();
// const username = 'username';
// const ref = database.ref("/users/" + username);

// Listen for changes on the user's database reference
// ref.on("value", (snapshot) => {
//   const data = snapshot.val();
  // Process the data for this user
  // ...
// });
