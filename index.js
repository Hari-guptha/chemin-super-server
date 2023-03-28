const express = require('express');
const bodyParser = require('body-parser');
const app = express();

var buttonValue1 = 0
var buttonValue2 = 0
var buttonValue3 = 0
var hum = 0;
var temp = 0;

app.use(bodyParser.json());
app.set('view engine', 'ejs');
app.use(express.static("views"))
app.use(express.urlencoded({ extended: true }));

app.get('/', (req, res) => {
    res.render("index.ejs")

})

app.post("/post1", (req, res) => {
    buttonValue1 = req.body.value;
});
app.post("/post2", (req, res) => {
    buttonValue2 = req.body.value;
});
app.post("/post3", (req, res) => {
    buttonValue3 = req.body.value;
});

app.get("/fun1",(req,res)=>{
    res.send(`${buttonValue1}`);
})
app.get("/fun2",(req,res)=>{
    res.send(`${buttonValue2}`);
})
app.get("/fun3",(req,res)=>{
    res.send(`${buttonValue3}`);
})
app.post("/temphum",(req,res)=>{
    temp = req.body.temp;
    hum = req.body.hum;
    console.log(`Received temperature: ${temp}, humidity: ${hum}`);
    res.sendStatus(200);
    
})

app.get("/getsense",(req,res)=>{
    res.send(`Received temperature: ${temp}, humidity: ${hum}`)
})

app.listen(4000)