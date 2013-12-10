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
		animation.Play("test_ouverture_porte_trigger_level1");
	}
	
	public void OnTriggeredStay () {
	}
	
	public void OnTriggeredExit () {
		animation.Play("test_ouverture_porte_trigger_level1_revert");
	}
}
