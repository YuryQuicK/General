const express = require('express')
const axios = require('axios')
const cheerio = require('cheerio')
const mustache = require('mustache')
const fs = require('fs')

const PORT = '3000'

//массив для IP
const ipArr = []

ipArr.push('192.168.30.0')
ipArr.push('192.168.30.1')
ipArr.push('192.168.30.2')
ipArr.push('192.168.30.3')

//массив для Url
const urlArr = []

// const sec = 1000
// const min = 60000
// const delay = 1 * sec

// части html кода
const htmlFirstPart = '<!DOCTYPE html><html lang="ru"><head><meta charset="UTF-8"><title>Мониторинг температуры</title></head><body><table align="center" border="1" cellspacing="0" width="40%" style="text-align: center;"><tr><th>IP-адрес</th><th>Температура</th></tr><form id="form" action="/" method="get">'
var htmlMiddlePart = ''
const htmlLastPart = "</form></table><script>let form = document.getElementById('form');form.submit();</script><script>let sec = 1000; let min = 60000; let delay = 5 * sec; let form = document.getElementById('form'); setInterval(() => {form.submit()}, delay);</script></body></html>"
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
    htmlMiddlePart += rowFirstPart + ip + rowSecondPart + `{{value` + i.toString() + '}}' + rowThirdPart
    //console.log(middlePart)
})
html = htmlFirstPart + htmlMiddlePart + htmlLastPart

const app = express()

app.get('/', (req, res) => {
    // рендер тут!
    res.send(html)
})

// ни к чему ещё один запрос
// app.get('getValue', (req, res) => {
//     urlArr.forEach(url => {
//         axios(url)
//             .then(response => {
//             const html = response.data
//             console.log(html)
//             })
    
//     });
// })

//const fd = fs.openSync('log.txt', 'w')

//setInterval(() => console.log('setInterval'), delay)

// setInterval(() => {
//     for (let i = 0; i < 2; i++) {
//         //fs.writeSync(fd, 'data data ')
//         fs.appendFileSync('log1' + '.txt', 'NewData ')
//         console.log('log is wrote')
//     }
// }, delay)

app.listen(PORT, () => console.log(`server running on PORT ${PORT}`))

// после заполнения массива ipArr получаем массив Url.
// записываем первую часть кода в переменную html. Добавлятем ip и данные, полученные по Url, в html
// Далее дописываем последнюю часть файла и открываем сайт.
// после с определённым интервалом получаем значения по url и рендерим их на сайт, а так же пишем логи.

// 2 массива: 1-ый с IP, 2-ой с Url
// firstPart lastPart middlePart(содержит все строки с данными(<tr></tr>))
// использовать метод form.submit()
// использовать два скрипта один из которых выполняется в самом начале, после 