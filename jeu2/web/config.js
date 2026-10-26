// Configuration du module Emscripten : le canvas du jeu et le message de chargement.
// Fichier à part : les règles de sécurité du site interdisent les scripts dans la page.
var Module = {
  canvas: (function () {
    var canvas = document.getElementById("canvas");
    canvas.addEventListener("contextmenu", function (e) { e.preventDefault(); });
    return canvas;
  })(),
  setStatus: function (texte) {
    var etat = document.getElementById("chargement");
    var progression = /\((\d+(?:\.\d+)?)\/(\d+)\)/.exec(texte || "");
    if (!texte) etat.hidden = true;
    else if (progression) etat.textContent = "Chargement du jeu… " + Math.round(100 * progression[1] / progression[2]) + " %";
  },
  onAbort: function () {
    document.getElementById("chargement").textContent = "Le jeu n'a pas pu démarrer dans ce navigateur. Essayez avec Chrome ou Firefox.";
  },
};
