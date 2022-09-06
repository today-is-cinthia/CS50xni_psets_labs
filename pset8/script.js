const likeBtn = document.querySelector(".like__btn");
const likeBtn2 = document.querySelector(".likebtn2");
const likeBtn3 = document.querySelector(".likebtn3");
let likeIcon = document.querySelector("#icon");
let likeIcon2 = document.querySelector("#icon2");
let likeIcon3 = document.querySelector("#icon3");
let count = document.querySelector("#count");
let count2 = document.querySelector("#count2");
let count3 = document.querySelector("#count3");

let clicked = false;


likeBtn.addEventListener("click", () => {
  if (!clicked) {
    clicked = true;
    likeIcon.innerHTML = `<i class="fas fa-thumbs-up"></i>`;
    count.textContent++;
  } else {
    clicked = false;
    likeIcon.innerHTML = `<i class="far fa-thumbs-up"></i>`;
    count.textContent--;
  }
});

likeBtn2.addEventListener("click", () => {
    if (!clicked) {
      clicked = true;
      likeIcon2.innerHTML = `<i class="fas fa-thumbs-up"></i>`;
      count2.textContent++;
    } else {
      clicked = false;
      likeIcon2.innerHTML = `<i class="far fa-thumbs-up"></i>`;
      count2.textContent--;
    }
  });
  
likeBtn3.addEventListener("click", () => {
    if (!clicked) {
      clicked = true;
      likeIcon3.innerHTML = `<i class="fas fa-thumbs-up"></i>`;
      count3.textContent++;
    } else {
      clicked = false;
      likeIcon3.innerHTML = `<i class="far fa-thumbs-up"></i>`;
      count3.textContent--;
    }
  });
