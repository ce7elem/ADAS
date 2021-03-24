import Vue from "vue";
import App from "./App.vue";
import Buefy from "buefy";
import "buefy/dist/buefy.css";

import VueSocketIO from 'vue-socket.io'
 
Vue.use(new VueSocketIO({
    debug: true,
    // connection: 'http://localhost',
    connection: 'http://192.168.43.124',
}))

Vue.config.productionTip = false;

Vue.use(Buefy);

new Vue({
  render: h => h(App)
}).$mount("#app");