using UnityEngine;
using System.Collections;

public class LaserBeam : MonoBehaviour {

	public GameObject crystal;
	public GameObject laserDirection;
	public GameObject beam;
	
	bool wasColliding;
	
	// Use this for initialization
	void Start () {
		wasColliding = false;
	}
	
	// Update is called once per frame
	void Update () {
		RaycastHit hit;
		
		Physics.Raycast(
			beam.transform.position,
			laserDirection.transform.position - beam.transform.position,
			out hit
		);
		Debug.DrawRay(
			beam.transform.position,
			(laserDirection.transform.position - beam.transform.position) * 1000,
			Color.blue,
			0
		);
		Debug.Log(hit.collider.name);
		if (hit.collider.gameObject.layer == 8) // crystal
		{
			if (wasColliding) {
				crystal.SendMessage("OnTriggeredStay");
			} else {
				wasColliding = true;
				crystal.SendMessage("OnTriggeredEnter");
			}
		} else if (wasColliding) {
			wasColliding = false;
			crystal.SendMessage("OnTriggeredExit");
		}
	}
}
