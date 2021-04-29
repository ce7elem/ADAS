<template>
	<div id="app">
		<div class="hero is-fullheight">
			<button 
        class="button is-danger is-large" 
        style="position: absolute; top: 20px; right: 20px; z-index: 10000" 
        @click="$refs.myBottomSheet.open()"
      >
      <!--
        @click="isComponentModalActive = !isComponentModalActive"
      -->
				🍔
			</button>
      <vue-bottom-sheet ref="myBottomSheet" style="z-index: 999999">
        <div><h1>Autopilot</h1></div>
        <button
          class="button is-danger"
          @click="input({dir: 'RESUME_AUTO'}); $refs.myBottomSheet.close();"
        >
          Enable Autopilot
        </button>
        <div style="height: 50px"></div>
      </vue-bottom-sheet>
			<Control v-if="!isComponentModalActive" @input="input"/>
<!-- 			<b-carousel @change="changeView" :indicator="false" :arrow="false" :pause-hover="false" :autoplay="false">
				<b-carousel-item v-for="(currentComponent, i) in components" :key="i" class="is-fullheight">
					<component
						v-bind:is="currentComponent"
						:message="message" :todos="todos"
					></component>
				</b-carousel-item>
			</b-carousel>
 -->			<b-modal :active.sync="isComponentModalActive" full-screen :can-cancel="true">
				<!-- <modal-form v-bind="formProps"></modal-form> -->
				<Fridge/>
			</b-modal>
		</div>

    <!--
		<section class="section hero is-primary has-text-black">
			<twemoji-textarea
				:emojiData="emojiDataAll" 
				:emojiGroups="emojiGroups"
				@contentChanged="input"
				@enterKey="enter"
				ref="textarea"
				enableSendBtn
				:searchEmojiPlaceholder="placeholder"
				:content="content"
			>
			</twemoji-textarea>
		</section>
    -->
	</div>
</template>

<script>
import Control from './components/Control.vue'
import Fridge from './components/Fridge.vue'

/*import {
	TwemojiTextarea
} from '@kevinfaguiar/vue-twemoji-picker';
*/
export default {
	name: 'App',
	data: () => ({
		isComponentModalActive: false,
		components: ["Control", "Fridge"],
		currView: 0,
		content: '',

		message: "",
	}),
	components: {
		Control, Fridge, //'twemoji-textarea': TwemojiTextarea
	},
	methods: {
		changeView: function (data) {
			this.currView = data
			// window.console.log(data);
		},

		input(d){
			console.log(d.dir)
			this.$socket.emit('input', d.dir);
		},
	},

	sockets: {
		updateMsg: function (data) {
			this.$data.message = data.message
		},

		updateTasks: function (data) {
			this.$data.todos = data
		}
	}
}
</script>

<style>
#app {
	font-family: Avenir, Helvetica, Arial, sans-serif;
	-webkit-font-smoothing: antialiased;
	-moz-osx-font-smoothing: grayscale;
	text-align: center;
	color: #2c3e50;
}

.carousel {
	margin: 0;
	padding: 0;
} 

</style>
