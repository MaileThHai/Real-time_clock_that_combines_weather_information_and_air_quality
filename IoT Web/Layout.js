
  // Your web app's Firebase configuration
  const firebaseConfig = {
    apiKey: "AIzaSyCYTDJmHHIh62myuNlygx4R1gmxU2ITVdg",
    authDomain: "realtimeclock-weather.firebaseapp.com",
    databaseURL: "https://realtimeclock-weather-default-rtdb.firebaseio.com",
    projectId: "realtimeclock-weather",
    storageBucket: "realtimeclock-weather.appspot.com",
    messagingSenderId: "488996652465",
    appId: "1:488996652465:web:9e0041f06c6feac6f2a990"
  };
    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);
    var database = firebase.database();
    
    
    // Auto load Temperature-------------------------
    firebase.database().ref("/realtimeclock-weather/R_Temperature").on("value",function(snapshot){
      var nd = snapshot.val();  
      document.getElementById("Temperature").innerHTML = nd;
      console.log(nd);
    });
    firebase.database().ref("/realtimeclock-weather/R_Humidity").on("value",function(snapshot){
      var nd = snapshot.val();  
      document.getElementById("Humidity").innerHTML = nd;
      console.log(nd);
    });
    firebase.database().ref("/realtimeclock-weather/R_AirQuality").on("value",function(snapshot){
      var nd = snapshot.val();  
      document.getElementById("AirQuality").innerHTML = nd;
      console.log(nd);
    });
  
    // firebase.database().ref("/realtimeclock-weather").on("value",function(snapshot){
    //   if(snapshot.exists()){
    //       console.log(snapshot.val())
    //       var CB1_status = snapshot.val()
    //       var CB2_status = snapshot.val()
    //       var CB3_status = snapshot.val()

    //       //CB1
    //       if (CB1_status["CB1"] == "ON"){
    //         document.getElementById("cb1_img").src = "https://png2.cleanpng.com/sh/4cf40b6c8bd4fd0701f4d3070ec449ec/L0KzQYm3WMIyN6h7iJH0aYP2gLBuTgRpbaNyh99udHX1PbTsjQNqfaQyfNdwcnXoPcXsjgBmepJ5jeRuLXbkeMPsjvhmcaUyjNd2cHX1ccX8kvUucZR0huU2Mj23RIK0hwJmbV57fdV9b4KwebT2jwMueJJsfZ8AYkfmRrLqWPUzQWg2SpC8NEO6SIW7VsE2O2U9UKI9NUa8Qom4TwBvbz==/kisspng-thermometer-celsius-degree-temperature-fahrenheit-temperature-icons-2-441-free-vector-icons-page-5b7c6ac8e29712.3437844615348804569281.png";
    //         document.getElementById("SliderNgangId1").value = 1;
    //         output1.innerHTML = "SliderNgang1".value = 1}
    //       else{
    //         document.getElementById("cb1_img").src = "https://png2.cleanpng.com/sh/9b5710fa45d6a8fd31d2900cf1f04f7e/L0KzQYm3VMA5N6dtfZH0aYP2gLBuTfNwdaF6jNd7LXnmf7B6TfxiapD3eeZ4comwhLnskv1wdZZ5feQ2dHXwgLb5ggR2epYygNH9LYfkhLb5TcVia2preqRtYXa2drW8TskzO2g9TKgBMUW1Q4KBVsQ4P2g2T6o3cH7q/kisspng-computer-icons-laboratory-thermometer-temperature-hot-water-5ac9fb2daf3fd5.9237846615231864777178.png?fbclid=IwAR36RPXrewdy3ik9wzZVqp7hlOFgaJ2WSKNnB81msOYV_cSh579eJfeDmbc";
    //         document.getElementById("SliderNgangId1").value = 0;
    //         output1.innerHTML = "SliderNgang2".value = 0}
    
    //       //CB2
    //       if (CB2_status["CB2"] == "ON"){
    //         document.getElementById("cb2_img").src = "https://png2.cleanpng.com/sh/67c8ba7edd917935b61972cf218f8c49/L0KzQYm3VMIyN5pnfZH0aYP2gLBuTfNwdaF6jNd7LXnmf7B6Tf1wcaR5jeRuLXj4fbrrigR6Nahmjtc2bXBsg8X8kvUuPZJpedg7OUjlSbS9hsUvO2c7TKcCN0G0RYO7Usk5O2o3T6g6LoDxd1==/kisspng-computer-icons-moisture-humidity-wave-moisture-5adaf298b9c6f5.366457711524298392761.png";
    //         document.getElementById("SliderNgangId2").value = 1;
    //         output2.innerHTML = "SliderNgang2".value = 1}
    //       else{
    //         document.getElementById("cb2_img").src = "https://png2.cleanpng.com/sh/c36952a59cee31b135b0ae14dc7c7762/L0KzQYm3VMI2N6R0j5H0aYP2gLBuTfNwdaF6jNd7LXnmf7B6Tf1wcaR5jeRuLXj4fbrrigR6NZ50geV9dYLoPYbohcBjbmo8Sqk9YnO6PoaBVcM1OGQ5Sac7NEa6SIa8UcE3OV91htk=/kisspng-computer-icons-moisture-humidity-moisture-5ae0bf97274bc7.585340341524678551161.png";
    //         document.getElementById("SliderNgangId2").value = 0;
    //         output2.innerHTML = "SliderNgang2".value = 0}
    
    //       //CB3
    //       if (CB3_status["CB3"] == "ON"){
    //         document.getElementById("cb3_img").src = "https://png2.cleanpng.com/sh/248aa93faeb562e24a9fb819ef9abe6b/L0KzQoG4UcE0N5R3jpH9cnHxg8HokvVvfF5qhtd7Z4mwcbBrTgBwf5Z3Rdtsb36wc7E5Tflkd58yTdhqZXToQImCgckzbmozTqI9OUK6Qoi4VsA2Omo6TqQ9NkO2QXB3jvc=/transparent-energy-and-power-icon-co2-icon-5faede089a92f9.6049272716052956246331.png";
    //         document.getElementById("SliderNgangId4").value = 1;
    //         output4.innerHTML = "SliderNgang4".value = 1}
    //       else{
    //         document.getElementById("cb3_img").src = "https://png2.cleanpng.com/sh/9d27549f805a13f837bba24d0bfd0ef2/L0KzQYq4UMI3N6NrgJH9cnHxg8HokvVvfF5oeeRrb36webT2jr1kd2MygdV4bj3ofbr6kBlwdl5ue9H3LUXncoW4VfVnamk5UKsALkC0Q4a3UsI6OWY8SqIDM0G7Q4i8VMgveJ9s/transparent-carbon-icon-co2-icon-emission-icon-5db415efb84895.0135022915720831837548.png";
    //         document.getElementById("SliderNgangId4").value = 0;
    //         output4.innerHTML = "SliderNgang4".value = 0}
    //     }
    //     else
    //       console.log("No data available!")
    //   })


    //   var sliderNgang1 = document.getElementById("SliderNgangId1");
    //   var output1 = document.getElementById("SliderNgangValue1");
    //   var img1 = document.getElementById("cb1_img");
    //   output1.innerHTML = sliderNgang1.value;
    //   sliderNgang1.oninput = function(){
    //   output1.innerHTML = this.value;
    //   let getvalue1 = sliderNgang1.value;
    //   if(getvalue1==1){
    //     img1.setAttribute("src", "https://png2.cleanpng.com/sh/4cf40b6c8bd4fd0701f4d3070ec449ec/L0KzQYm3WMIyN6h7iJH0aYP2gLBuTgRpbaNyh99udHX1PbTsjQNqfaQyfNdwcnXoPcXsjgBmepJ5jeRuLXbkeMPsjvhmcaUyjNd2cHX1ccX8kvUucZR0huU2Mj23RIK0hwJmbV57fdV9b4KwebT2jwMueJJsfZ8AYkfmRrLqWPUzQWg2SpC8NEO6SIW7VsE2O2U9UKI9NUa8Qom4TwBvbz==/kisspng-thermometer-celsius-degree-temperature-fahrenheit-temperature-icons-2-441-free-vector-icons-page-5b7c6ac8e29712.3437844615348804569281.png")
    //     firebase.database().ref("/realtimeclock-weather").update({"CB1": "ON"})
    //     firebase.database().ref("/realtimeclock-weather/R_Temperature").on("value",function(snapshot){
    //       var nd = snapshot.val();  
    //       document.getElementById("Temperature").innerHTML = nd;
    //       console.log(nd);
    //     });
    //   }
    //   else{
    //     img1.setAttribute("src", "https://png2.cleanpng.com/sh/9b5710fa45d6a8fd31d2900cf1f04f7e/L0KzQYm3VMA5N6dtfZH0aYP2gLBuTfNwdaF6jNd7LXnmf7B6TfxiapD3eeZ4comwhLnskv1wdZZ5feQ2dHXwgLb5ggR2epYygNH9LYfkhLb5TcVia2preqRtYXa2drW8TskzO2g9TKgBMUW1Q4KBVsQ4P2g2T6o3cH7q/kisspng-computer-icons-laboratory-thermometer-temperature-hot-water-5ac9fb2daf3fd5.9237846615231864777178.png?fbclid=IwAR36RPXrewdy3ik9wzZVqp7hlOFgaJ2WSKNnB81msOYV_cSh579eJfeDmbc")
    //     firebase.database().ref("/realtimeclock-weather").update({"CB1": "OFF"})
    //     firebase.database().ref("/realtimeclock-weather").update({"R_Temperature": "OFF"})
    //   }
    // };
    
    // var sliderNgang2 = document.getElementById("SliderNgangId2");
    // var output2 = document.getElementById("SliderNgangValue2");
    // var img2 = document.getElementById("cb2_img");
    // output2.innerHTML = sliderNgang2.value;
    // sliderNgang2.oninput = function(){
    //   output2.innerHTML = this.value;
    //   let getvalue2 = sliderNgang2.value;
    //   if(getvalue2==1){
    //     img2.setAttribute("src", "https://png2.cleanpng.com/sh/67c8ba7edd917935b61972cf218f8c49/L0KzQYm3VMIyN5pnfZH0aYP2gLBuTfNwdaF6jNd7LXnmf7B6Tf1wcaR5jeRuLXj4fbrrigR6Nahmjtc2bXBsg8X8kvUuPZJpedg7OUjlSbS9hsUvO2c7TKcCN0G0RYO7Usk5O2o3T6g6LoDxd1==/kisspng-computer-icons-moisture-humidity-wave-moisture-5adaf298b9c6f5.366457711524298392761.png")
    //     firebase.database().ref("/realtimeclock-weather").update({"CB2": "ON"})
    //     firebase.database().ref("/realtimeclock-weather/R_Humidity").on("value",function(snapshot){
    //       var nd = snapshot.val();  
    //       document.getElementById("Humidity").innerHTML = nd;
    //       console.log(nd);
    //     });
    //   }
    //   else{
    //     img2.setAttribute("src", "https://png2.cleanpng.com/sh/c36952a59cee31b135b0ae14dc7c7762/L0KzQYm3VMI2N6R0j5H0aYP2gLBuTfNwdaF6jNd7LXnmf7B6Tf1wcaR5jeRuLXj4fbrrigR6NZ50geV9dYLoPYbohcBjbmo8Sqk9YnO6PoaBVcM1OGQ5Sac7NEa6SIa8UcE3OV91htk=/kisspng-computer-icons-moisture-humidity-moisture-5ae0bf97274bc7.585340341524678551161.png")
    //     firebase.database().ref("/realtimeclock-weather").update({"CB2": "OFF"})
    //     firebase.database().ref("/realtimeclock-weather").update({"R_Humidity": "OFF"})
    //   }
    // };
    
    // var sliderNgang4 = document.getElementById("SliderNgangId4");
    // var output4 = document.getElementById("SliderNgangValue4");
    // var img4 = document.getElementById("cb3_img");
    // output4.innerHTML = sliderNgang4.value;
    // sliderNgang4.oninput = function(){
    //   output4.innerHTML = this.value;
    //   let getvalue4 = sliderNgang4.value;
    //   if(getvalue4==1){
    //     img4.setAttribute("src", "https://png2.cleanpng.com/sh/248aa93faeb562e24a9fb819ef9abe6b/L0KzQoG4UcE0N5R3jpH9cnHxg8HokvVvfF5qhtd7Z4mwcbBrTgBwf5Z3Rdtsb36wc7E5Tflkd58yTdhqZXToQImCgckzbmozTqI9OUK6Qoi4VsA2Omo6TqQ9NkO2QXB3jvc=/transparent-energy-and-power-icon-co2-icon-5faede089a92f9.6049272716052956246331.png")
    //     firebase.database().ref("/realtimeclock-weather").update({"CB3": "ON"})
    //     firebase.database().ref("/realtimeclock-weather/R_AirQuality").on("value",function(snapshot){
    //       var nd = snapshot.val();  
    //       document.getElementById("Light").innerHTML = nd;
    //       console.log(nd);
    //     });
    //   }
    //   else{
    //     console.log("Off");
    //     img4.setAttribute("src", "https://png2.cleanpng.com/sh/9d27549f805a13f837bba24d0bfd0ef2/L0KzQYq4UMI3N6NrgJH9cnHxg8HokvVvfF5oeeRrb36webT2jr1kd2MygdV4bj3ofbr6kBlwdl5ue9H3LUXncoW4VfVnamk5UKsALkC0Q4a3UsI6OWY8SqIDM0G7Q4i8VMgveJ9s/transparent-carbon-icon-co2-icon-emission-icon-5db415efb84895.0135022915720831837548.png")
    //     firebase.database().ref("/realtimeclock-weather").update({"CB3": "OFF"})
    //   firebase.database().ref("/realtimeclock-weather").update({"R_AirQuality": "OFF"})
    //   }
    // };