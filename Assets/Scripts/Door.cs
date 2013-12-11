using UnityEngine;
using System.Collections;

public class Door : MonoBehaviour, ITriggered {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void OnTriggeredEnter () {
		Debug.Log ("Enter !");
		//animation["test_ouverture_porte_trigger_level1"].time = 0;
		animation["test_ouverture_porte_trigger_level1"].speed = 1;
		animation.Play("test_ouverture_porte_trigger_level1");
	}
	
	public void OnTriggeredStay () {
		Debug.Log ("Stay !");
	}
	
	public void OnTriggeredExit () {
		Debug.Log ("Exit !");
		//animation["test_ouverture_porte_trigger_level1"].time = animation["test_ouverture_porte_trigger_level1"].length;
		animation["test_ouverture_porte_trigger_level1"].speed = -1;
		animation.Play("test_ouverture_porte_trigger_level1");
	}
}
