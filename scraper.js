const express = require('express')
const axios = require('axios')
const cheerio = require('cheerio')
const fs = require('fs')

const PORT = '3000'

// массив для IP
const ipArr = []
ipArr.push('192.168.30.0')
ipArr.push('192.168.30.1')
ipArr.push('192.168.30.2')
ipArr.push('192.168.30.3')

// массив для Url
const urlArr = []

// массив для температур
var temp = []

// части html кода
const htmlFirstPart = '<!DOCTYPE html><html lang="ru"><head><meta charset="UTF-8"><title>Мониторинг температуры</title></head><body><table align="center" border="1" cellspacing="0" width="40%" style="text-align: center;"><tr><th>IP-адрес</th><th>Температура</th></tr><form id="form" action="/" method="get">'
var htmlMiddlePart = ''
const htmlLastPart = "</form></table><script>let sec = 1000; let min = 60000; let delay = 5 * sec; let form = document.getElementById('form'); setInterval(() => {form.submit()}, delay);</script></body></html>"
var html = ''

// части строки ip и температуры
const rowFirstPart = '<tr><td>'
const rowSecondPart = '</td><td>'
const rowThirdPart = '</td></tr>'

// части Url-строки
const urlFirstPart = 'http://'
const urlSecondPart = '/cgi-bin/scheme'

ipArr.forEach((ip, i) => {
    urlArr.push(urlFirstPart + ip + urlSecondPart)
})

// var obj = {}
// obj['length'] = ipArr.length
// ipArr.forEach((ip, i) => {
//     obj['value' + i.toString()] = ip;
// })
// console.log(obj)

const app = express()

function getTemp() {
    urlArr.forEach((url, i) => {
        axios(url)
            .then(response => {
            const html = response.data
            const $ = cheerio.load(html)
            const tempVal = $('.cell_v_0111').text()
            temp[i] = tempVal
            console.log(`temp of dev num ${i} = ` + tempVal)
            })
    })
}

setInterval(() => {
    getTemp()
    ipArr.forEach((ip, i) => {
        //fs.writeSync(fd, 'data data ')
        fs.appendFileSync(ip + '.txt', temp[i])
        console.log('log is wrote')
    })
}, 5000)

app.get('/', (req, res) => {
    temp.forEach((t, i) => {
        htmlMiddlePart += rowFirstPart + ipArr[i] + rowSecondPart + t + rowThirdPart
    })
    html = htmlFirstPart + htmlMiddlePart + htmlLastPart
    res.writeHead(200)
    res.send(html)
})

app.get('/getData', (req, res) => {
    var obj = {}
    obj['length'] = temp.length
    temp.forEach((temper, i) => {
        obj['value' + i.toString()] = temper;
    })
    res.writeHead(200)
    res.end(JSON.stringify(obj))
})

//const fd = fs.openSync('log.txt', 'w')

app.listen(PORT, () => console.log(`server running on PORT ${PORT}`))

// после заполнения массива ipArr получаем массив Url.
// записываем первую часть кода в переменную html. Добавлятем ip и данные, полученные по Url, в html
// Далее дописываем последнюю часть файла и открываем сайт.
// после с определённым интервалом получаем значения по url и рендерим их на сайт, а так же пишем логи.

// 2 массива: 1-ый с IP, 2-ой с Url
// firstPart lastPart middlePart(содержит все строки с данными(<tr></tr>))
// использовать метод form.submit()
// использовать два скрипта один из которых выполняется в самом начале, после

// заполняем массив с температурой и после при запросе от клиента передаём ему этот массив