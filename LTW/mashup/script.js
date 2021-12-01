const $ = (selector) => document.querySelector(selector);

const imgMap = {
  SKC: "https://upload.wikimedia.org/wikipedia/commons/thumb/e/e7/Gnome-weather-clear.svg/48px-Gnome-weather-clear.svg.png",
  FEW: "https://upload.wikimedia.org/wikipedia/commons/thumb/5/57/Gnome-weather-few-clouds.svg/48px-Gnome-weather-few-clouds.svg.png",
  SCT: "https://upload.wikimedia.org/wikipedia/commons/thumb/6/61/Gnome-weather-overcast.svg/48px-Gnome-weather-overcast.svg.png",
  BKN: "https://upload.wikimedia.org/wikipedia/commons/thumb/2/22/Gnome-weather-severe-alert.svg/48px-Gnome-weather-severe-alert.svg.png",
  OVC: "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f9/Gnome-weather-storm.svg/48px-Gnome-weather-storm.svg.png"
};

const changeImage = (id) => {
  //const mapId = id || $("select[name=imgSource]").value;
  //$("#icon").src = imgMap[mapId];
  $("#icon").src = imgMap[id];
}

const getWeather = async (cords) => {
  const req = `http://api.geonames.org/weatherJSON?formatted=true&north=${cords.north}&south=${cords.south}&east=${cords.east}&west=${cords.west}&username=twlab&style=full`

  const res = await fetch(req);
  const json = await res.json();
  const observations = json.weatherObservations;

  let cloudsCode;
  for (obs of observations) {
    if (!obs.cloudsCode) continue;
    cloudsCode = obs.cloudsCode;
    break;
  }
  console.log("code: ", cloudsCode);
  if (!cloudsCode || !imgMap[cloudsCode]) return;

  changeImage(cloudsCode);
}

const getCityWeather = async () => {
  const city = $("#cityBox").value;
  
  const req = `http://api.geonames.org/searchJSON?formatted=true&q=${city}&username=twlab&style=full`;
  const res = await fetch(req);
  const json = await res.json();

  const bbox = json.geonames[0].bbox;
  console.log(bbox);

  if (!bbox) return;
  await getWeather(bbox);
}
