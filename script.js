let dataCells = document.querySelectorAll('td');

fetch('./getData')
    .then(res => res.json())
    .then(obj => {
        let length = obj['length'];
        for (let i = 0; i < length; i++) {
            dataCells.forEach((cell, j) => {
                if (j % 2 != 0) {
                    cell.innerHTML = obj['value' + i.toString()];
                }
            });
        }
    });
