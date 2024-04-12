const express = require('express'); 
const { PrismaClient } = require('@prisma/client');
require('dotenv').config();
const prisma = new PrismaClient();
const app = express();
const PORT = process.env.PORT;
app.use(express.json());


app.post('/sensores', async (req, res)=>{
    console.log
    const sensor = await prisma.sensor.create({
        data: req.body
    }) 
    res.json(sensor);
});

app.get('/sensores', async (req, res)=>{
    const sensor = await prisma.sensor.findMany();
    res.json(sensor);
})





app.listen(PORT, () => {
console.log(`Server is running on port ${PORT}`);
});
