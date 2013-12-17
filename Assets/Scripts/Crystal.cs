using UnityEngine;
using System.Collections;

public class Crystal : MonoBehaviour, ITriggered {
	
	public GameObject trigger;

	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
	}
	
	public void OnTriggeredEnter () {
		trigger.SendMessage("OnTriggeredEnter");
		animation.Play ("Crystal_White_To_Red_Animation");
	}
	
	public void OnTriggeredStay () {
		trigger.SendMessage("OnTriggeredStay");
	}
	
	public void OnTriggeredExit () {
		trigger.SendMessage("OnTriggeredExit");
		animation.Play ("Crystal_Red_To_White_Animation");
	}
}
