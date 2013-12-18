using UnityEngine;
using System.Collections;

public class Crystal : MonoBehaviour, ITriggered {
	
	public GameObject trigger;
	private AudioSource[] audios;
	AudioSource crystalSwitchOnAudio;
	AudioSource crystalSwitchOffAudio;
	
	// Use this for initialization
	void Start () {
		 audios = GetComponents<AudioSource>();
		crystalSwitchOnAudio = audios[0];
		crystalSwitchOffAudio = audios[1];
	}
	
	// Update is called once per frame
	void Update () {
		
	}
	
	public void OnTriggeredEnter () {
		crystalSwitchOnAudio.Play();
		trigger.SendMessage("OnTriggeredEnter");
		animation.Play ("Crystal_White_To_Red_Animation");
	}
	
	public void OnTriggeredStay () {
		trigger.SendMessage("OnTriggeredStay");
	}
	
	public void OnTriggeredExit () {
		crystalSwitchOffAudio.Play();
		trigger.SendMessage("OnTriggeredExit");
		animation.Play ("Crystal_Red_To_White_Animation");
	}
}
