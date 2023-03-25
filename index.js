const express = require('express');
const app = express();

app.set('view engine', 'ejs');
app.use(express.static("views"))

app.get('/', (req, res) => {
    res.render("index.ejs")
})

app.get('/api', (req, res) => {
    res.send("po da venna")
})

app.get('/on', (req, res) => {
    res.send("1")
})
app.get('/off', (req, res) => {
    res.send("0")
})


app.post('/home', (req, res) => {
    res.send("we are good")
})


app.listen(4000)