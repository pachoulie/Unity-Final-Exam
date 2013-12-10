using UnityEngine;
using System.Collections;

public class Slab : MonoBehaviour {
	
	public GameObject trigger;
	
	// Use this for initialization
	void Start () {
		//trigger = (ITriggered) objectToTrigger;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter (Collider collider) {
		trigger.SendMessage("OnTriggeredEnter");
		animation["slab_pressure"].speed = 1;
		animation["slab_pressure"].time = 0;
		animation.Play();
	}

	void OnTriggerExit (Collider collider) {
		trigger.SendMessage("OnTriggeredExit");
		animation["slab_pressure"].time = animation["slab_pressure"].length;
		animation["slab_pressure"].speed = -1;
		animation.Play ();
	}
	
	void OnTriggerStay (Collider collider) {
		trigger.SendMessage("OnTriggeredStay");
	}
}
