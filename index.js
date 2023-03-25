const express = require('express');
const app = express();

app.set('view engine', 'ejs');
app.use(express.static("views"))

app.get('/api', (req, res) => {
    res.render("index.ejs")
})

app.post('/home', (req, res) => {
    res.send("we are good")
})


app.listen(4000)