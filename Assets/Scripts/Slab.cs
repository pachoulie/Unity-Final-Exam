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
		animation.Play("slab_pressure");
	}

	void OnTriggerExit (Collider collider) {
		trigger.SendMessage("OnTriggeredExit");
		//animation["slab_pressure"].time = animation["slab_pressure"].length;
		if (!animation.isPlaying)
			animation["slab_pressure"].time = animation["slab_pressure"].length;
		animation["slab_pressure"].speed = -1;
		animation.Play ("slab_pressure");
	}
	
	void OnTriggerStay (Collider collider) {
		trigger.SendMessage("OnTriggeredStay");
	}
}
