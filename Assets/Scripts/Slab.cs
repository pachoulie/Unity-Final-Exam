using UnityEngine;
using System.Collections;

public class Slab : MonoBehaviour {
	
	//public ITriggered trigger;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter (Collider collider) {
		//trigger.OnSlabEnter();
	}

	void OnTriggerExit (Collider collider) {
		//trigger.OnSlabExit();
	}
	
	void OnTriggerStay (Collider collider) {
		//trigger.OnSlabStay();
	}
}
