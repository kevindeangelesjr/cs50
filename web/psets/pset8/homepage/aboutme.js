let bio_text = '<h5>Welcome to my page!  My name is Kevin.</h5><p>I\'ve lived in Pennsylvania all of my life, mostly in the greater Philadelphia area.\
 Currently, I live in Phoenixville, PA in Chester County.  Professionally, I am a Red Hat Certified Engineer (RHCE), and I work as a Linux systems administrator.\
  I am currently teaching myself web development, and this site is one of my first projects.  You can use the Interests dropdown above to learn more about my current hobbies and pursuits.</p>'
let contact_text = '<p><strong>email</strong>: kevindeangelesjr@gmail.com</p>'

document.querySelector('#bio-btn').onclick = function() {

    if (document.querySelector('#bio').innerHTML === '')
    {
        document.querySelector('#bio').innerHTML = bio_text;
        document.querySelector('#bio-section').style.background = '#D0D2FF';
    }

    else
    {
        document.querySelector('#bio').innerHTML = '';
        document.querySelector('#bio-section').style.background = '';
    }
}

document.querySelector('#contact-btn').onclick = function() {

    if (document.querySelector('#contact').innerHTML === '')
    {
        document.querySelector('#contact').innerHTML = contact_text;
        document.querySelector('#contact-section').style.background = '#D0D2FF';
    }

    else
    {
        document.querySelector('#contact').innerHTML = '';
        document.querySelector('#contact-section').style.background = '';
    }
}