let score = JSON.parse(localStorage.getItem('score')) || {
    wins: 0,
    losses: 0,
    ties: 0
};


updateScoreElement();

document.querySelector('.js-result')
    .innerHTML = `${result}`;
document.querySelector('.js-moves')
    .innerHTML = `You ${yourMove} - ${ComputerMove} Computer`;



function computerMovePick() {

    let ComputerMove = '';
    let randomNumber;

    randomNumber = Math.random();

    if (randomNumber >= 0 && randomNumber < 1 / 3) {
        ComputerMove = 'Rock';
    } else if (randomNumber >= 1 / 3 && randomNumber < 2 / 3) {
        ComputerMove = 'Paper';
    } else if (randomNumber >= 2 / 3 && randomNumber < 1) {
        ComputerMove = 'Scissors';
    }

    return ComputerMove;

}

function playGame(yourMove) {

    const ComputerMove = computerMovePick();

    let result = '';

    if (ComputerMove === yourMove) {
        result = 'Tie.';
        score.ties += 1;

    } else if (ComputerMove === 'Rock' && yourMove === 'Scissors') {
        result = 'You lose.';
        score.losses += 1;

    } else if (ComputerMove === 'Scissors' && yourMove === 'Rock') {
        result = 'You win.';
        score.wins += 1;

    } else if (ComputerMove === 'Paper' && yourMove === 'Scissors') {
        result = 'You win.';
        score.wins += 1;

    } else if (ComputerMove === 'Scissors' && yourMove === 'Paper') {
        result = 'You lose.';
        score.losses += 1;
    } else if (ComputerMove === 'Paper' && yourMove === 'Rock') {
        result = 'You lose.';
        score.losses += 1;
    } else if (ComputerMove === 'Rock' && yourMove === 'Paper') {
        result = 'You win.';
        score.wins += 1;
    }

    updateScoreElement();

    document.querySelector('.js-result')
        .innerHTML = `${result}`;
    document.querySelector('.js-moves')
        .innerHTML = `You 
      <img src="Emoji/${yourMove}-emoji.png" class="play-emoji"> 
      <img src="Emoji/${ComputerMove}-emoji.png" class="play-emoji"> 
      Computer`;

    localStorage.setItem('score', JSON.stringify(score));

}

function updateScoreElement() {
    document.querySelector('.js-score')
        .innerHTML = `Wins: ${score.wins}, Losses: ${score.losses}, Tie: ${score.ties}`;
}

/*function updateresultElement() {
  document.querySelector('.js-result')
      .innerHTML = `${result}.`;
}

function movesElement() {
  document.querySelector('.js-moves')
      .innerHTML = `You ${yourMove} - ${ComputerMove} Computer`;
}*/